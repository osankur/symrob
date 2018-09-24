"""
Given an AIG file and a time configuration file TIME which contains a pair of integers for each latch. The TAWRITER class constructs a timed automaton which simulates this circuit with the following timing constraints.
For each latch, we are given the pair (delay[0],delay[1]). The circuit simulation can perform a new cycle if only if for each latch l:
- if l is about to change from 1 to 0, then at least delay[0] time units have passed since the value was changed to 1
- if l is about to change from 0 to 1, then at least delay[1] time units have passed since the value was changed to 0
If the value of l does not change, then there is no time constraint.

The present version computes an urgent model where each cycle is executed as soon as possible.
A deadlock is present iff there is a deadlock in the model (in the sense of Uppaal) or
location "dead" is reachable.

Latch names are obtained by replacing &lt;, &gt; characters by _ and by prefixing them by L
Input names are obtained ..................................
Clock names are obtained .................................. and by prefixing them by x_

In this version, we only consider those latches whose names contain "state",
and we actually take the first half of them to make clock constraints
"""
import sys
import argparse
import log
from itertools import chain
import StringIO

# when set to true, boolean operations are translated as arithmetic ones such as && -&gt; *
numeric_mode = True

from aiger_swig.aiger_wrap import (
    get_aiger_symbol,
    aiger_init,
    aiger_open_and_read_from_file,
    aiger_is_input,
    aiger_is_latch,
    aiger_is_and,
    aiger_add_and,
    aiger_add_output,
    aiger_symbol,
    aiger_open_and_write_to_file,
    aiger_redefine_input_as_and,
    aiger_remove_outputs,
)
from aig import (
    AIG,
    strip_lit,
    lit_is_negated,
    symbol_lit,
    negate_lit
)
from pat_ta_txt import *

class TAWRITER:
    def __init__(self, aiger_file_name, time_file_name, factor=1):
        self.aig = AIG(aiger_file_name, False)
        self.lit_to_formula = dict()
        self._cached_transition = None
        self.factor = factor
        self.delays = self._read_delays(time_file_name)

    def _read_delays(self, time_file_name):
        delays = dict()
        latches = [x.lit for x in self.aig.iterate_latches()]
        with open(time_file_name,'r') as fp:
            for l in range(len(latches)):
                s = fp.readline()
                if s <> "":
                #print "Doing line:&lt;{0}&gt;".format(s)
                #print s.split(" ")
                    si = map(lambda x: int(x), s.split(" "))
                    assert(len(si) == 2)
                    delays[latches[l]] = (si[0] * self.factor, si[1] * self.factor)
                else:
                    delays[latches[l]] = (self.factor,self.factor)
        log.DBG_MSG("Latch delays: " + str(delays))
        return delays

    def set_lit2formula(self, lit, s):
        self.lit_to_formula[lit] = s

    """ Name of stripped literal which must be an input or latch """
    def name_of(self, lit):
        assert(lit == strip_lit(lit))
        (intput, latch, and_gate) = self.aig.get_lit_type(lit)
        # is it an input, latch, gate or constant
        #print &gt;&gt; sys.stderr, "lit", lit, (input,latch,and_gate)
        if latch:
            return "L"+self.aig.get_lit_name(lit).replace("&lt;", "_").replace("&gt;", "_");
        elif input:
            # Boolean variables are encoded as 1-bit integers for now
            return "I"+self.aig.get_lit_name(lit).replace("&lt;", "_").replace("&gt;", "_");
        else:
            raise "And gates or constant inputs have no name"

    def lit2formula(self, lit):
        if lit in self.lit_to_formula:
            return self.lit_to_formula[lit]
        # get stripped lit
        stripped_lit = strip_lit(lit)
        is_neg = lit_is_negated(lit)
        (input, latch, and_gate) = self.aig.get_lit_type(stripped_lit)
        # is it an input, latch, gate or constant
        if input or latch:
            # Boolean variables are encoded as 1-bit integers for now
            result = "({0})".format(self.name_of(stripped_lit))
        elif and_gate:
            if numeric_mode:
                result = ("({0} * {1})".format(self.lit2formula(and_gate.rhs0),
                      self.lit2formula(and_gate.rhs1)))
            else:
                result = ("({0} &amp;&amp; {1})".format(self.lit2formula(and_gate.rhs0),
                      self.lit2formula(and_gate.rhs1)))
        else:  # 0 literal, 1 literal and errors
            result = "0" # this means false
        # cache result
        self.lit_to_formula[stripped_lit] = result
        if is_neg:
            if result == "0":
                result = "1"
            else:
                if numeric_mode:
                    result = "(1-{0})".format(result)
                else:
                    result = "!{0}".format(result)
            self.lit_to_formula[lit] = result
        return result

    def get_next_funcs(self):
        if self._cached_transition is not None:
            return self._cached_transition
        vec = dict()
        for x in self.aig.iterate_latches():
            vec[x.lit] = self.lit2formula(x.next)
        self._cached_transition = vec
        return vec

    """
    Given K, make timed automaton model that restricts each cycle to K time units.
    """
    def get_cycle_time_model(self, nb_clocked_latches, K):
        K = K * self.factor
        latch_locations = dict()
        # clock name associated to given lit which is a latch
        clock_name = dict()
        nta = NTA()
        temp = Template("Circuit")
        nta.add_template(temp)

        decl = StringIO.StringIO()
        init = Location("Init", urgent=True,initial=True)
        deadlock = Location("dead", error=True)

        latch_list = list(self.aig.iterate_latches())
        latch_num = len(latch_list)

        clocked_latches = filter(lambda x: "state" in self.name_of(x.lit), latch_list)
        clocked_latches = latch_list
        clocked_latches = clocked_latches[0:nb_clocked_latches]
        clock_decl = []
        print >> sys.stderr, "Clocked latches: "
        for x in clocked_latches:
            print >> sys.stderr, x.lit, " ", self.name_of(x.lit), self.delays[x.lit]
            clock_name[x.lit] = "x_" + str(x.lit)
            clock_decl.append(clock_name[x.lit])
        clock_decl.append("t")
        temp.decl = ("clock: " + ", ".join(clock_decl) + ";")
        last_location = init
        input_list = list(chain(self.aig.iterate_uncontrollable_inputs(),self.aig.iterate_controllable_inputs()))
        print >> decl, "var fdead :{0..1} = 0;"
        for i in input_list:
            print >> decl, "var {0}".format(self.name_of(i.lit)), ":{0..1} = 0;"
            loc_after_i = Location("JustSet"+self.name_of(i.lit), urgent=True)
            tr0 = Transition(last_location, loc_after_i, disc_up="{0} = 0;".format(self.name_of(i.lit)))
            tr1 = Transition(last_location, loc_after_i, disc_up="{0} = 1;".format(self.name_of(i.lit)))
            temp.add_transition(tr0)
            temp.add_transition(tr1)
            last_location = loc_after_i
            pass

        next_funcs = self.get_next_funcs()

        for x in latch_list:
            print >> decl, "var {0} ".format(self.name_of(x.lit)),  ":{0..1} = 0;"
            if not x in clocked_latches:
                continue
            latch_locations[x.lit] = Location("Updated"+ self.name_of(x.lit), urgent=True)

            # Basically, we add the following transitions but use intermediary states
            # with invariants so that all transitions are urgent
            # updated(l_{i-1},urg) ---- f(vec(l),I) = l_i ----&gt; updated(l_{i+1})
            # updated(l_{i-1},urg) ---- f(vec(l),I) = 0 && l_i = 1, x_i &gt;= D_i^1, l_i := 0, x_i := 0 ----&gt; updated(l_{i},urg)
            # updated(l_{i-1},urg) ---- f(vec(l),I) = 0 && l_i = 1, x_i &lt; D_i^1, l_i := 0, x_i := 0 ----&gt; will_become1_nurg(l_{i})
            # symmetrically for when the new value is 1
            # will_become1_nurg(l_{i},invar:x_i&lt;=D_i^1) ---- x_i &gt;= D_i^0, l_i := 1, x_i := 0 ----&gt; updated(l_{i}, urg)

            # if the value does not change:
            disc_g = "{0} == {1}".format(self.name_of(x.lit), next_funcs[x.lit])
            tr = Transition(last_location, latch_locations[x.lit], disc_guard=disc_g)
            temp.add_transition(tr)

            # if it changes but the delay is already respected, move on directly
            disc_g = "{0} == 1 &amp;&amp; {0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit])
            clock_g = "{0} &gt;= {1}".format(clock_name[x.lit], self.delays[x.lit][0])
            temp.add_transition(Transition(last_location, latch_locations[x.lit], disc_guard=disc_g, guard=clock_g))
            g = "{0} == 0 &amp;&amp; {0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit])
            clock_g = "{0} &gt;= {1}".format(clock_name[x.lit], self.delays[x.lit][1])
            temp.add_transition(Transition(last_location, latch_locations[x.lit], guard=clock_g, disc_guard=g))

            # if we have to wait to respect the delay go to specific wait state and wait precisely for the delay (matching invariant + guard)
            loc0 = Location(latch_locations[x.lit].name + "_becomes0")
            loc0.set_invariant("{0} &lt;= {1}".format(clock_name[x.lit], self.delays[x.lit][0]))
            loc1 = Location(latch_locations[x.lit].name + "_becomes1")
            loc1.set_invariant("{0} &lt;= {1}".format(clock_name[x.lit], self.delays[x.lit][1]))

            g = "{0} == 1 &amp;&amp; {0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit])
            if self.delays[x.lit][0] > 0:
                clock_g =  "{0} &lt;= {1}".format( clock_name[x.lit], self.delays[x.lit][0]-1)
            else:
                clock_g = ""
            tr = Transition(last_location, loc0, guard=clock_g, disc_guard=g)
            temp.add_transition(tr)

            up="{0} = {1};".format(self.name_of(x.lit), next_funcs[x.lit])
            g = "{0} &gt;= {1}".format(clock_name[x.lit], self.delays[x.lit][0])
            tr = Transition(loc0, latch_locations[x.lit], guard=g, disc_up=up, reset=clock_name[x.lit])
            temp.add_transition(tr)

            g = "{0} == 0 &amp;&amp; {0} != {1} ".format(self.name_of(x.lit), next_funcs[x.lit])
            if self.delays[x.lit][1] > 0:
                clock_g = "{0} &lt;= {1}".format( clock_name[x.lit], self.delays[x.lit][1]-1)
            else:
                clock_g = ""
            tr = Transition(last_location, loc1, guard=clock_g,disc_guard=g)
            temp.add_transition(tr)

            up = "{0} = {1};".format(self.name_of(x.lit), next_funcs[x.lit])
            g = "{0} &gt;= {1}".format(clock_name[x.lit], self.delays[x.lit][1])
            tr = Transition(loc1, latch_locations[x.lit], guard=g, disc_up=up, reset=clock_name[x.lit])
            temp.add_transition(tr)

            last_location = latch_locations[x.lit]
            pass
        go_deadlock=Transition(last_location, deadlock, guard="t &gt;={0}".format(str(K+1)), disc_up="fdead = 1;")
        come_back= Transition(last_location, init, guard="t &lt;= {0}".format(str(K)), reset="t")
        temp.add_transition(come_back)
        temp.add_transition(go_deadlock)
        last_location = init
        print >> decl, "System = Circuit();"
        print >> decl, "#define Dead fdead==1;"
        print >> decl, "#assert System reaches Dead;"
        nta.set_declaration(decl.getvalue())
        nta.dump()

    def test(self):
        vec = self.get_next_funcs();
        for x in vec:
            print >> sys.stderr, "NEXT(",x,")"
            print >> sys.stderr, vec[x]
            print >> sys.stderr, ""

def main():
    parser = argparse.ArgumentParser(description="AIG Format Based Synth")
    parser.add_argument("spec", metavar="spec", type=str,
                        help="input specification in extended AIGER format")
    parser.add_argument("time", metavar="time", type=str,
                        help="time specifications")
    parser.add_argument("clocked_latches", metavar="clocked", type=int,
                        help="number of clocked latches")
    parser.add_argument("bound", metavar="bound", type=int,
                        help="time bound to verify")
    parser.add_argument("-v", "--verbose_level", dest="verbose_level",
                        default="", required=False,
                        help="Verbose level = (D)ebug, (W)arnings, " +
                             "(L)og messages, (B)DD dot dumps")
    parser.add_argument("-f", "--factor", dest="factor", type=int,
                        required=False, default=1,
                        help=("Factor by which all constants are to be multiplied"))
    args = parser.parse_args()
    log.parse_verbose_level(args.verbose_level)
    # realizability / synthesis
    tawriter = TAWRITER(args.spec, args.time, args.factor)
    # tawriter.test();
    # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
    tawriter.get_cycle_time_model(args.clocked_latches, args.bound)

def test():
    nta = NTA()
    template = Template("Circuit")
    nta.set_declaration("System = Circuit();")
    loc1 = Location("init", initial=True)
    loc2 = Location("end", error=True)
    template.add_transition(Transition(loc1,loc2))
    nta.add_template(template)
    nta.dump()

if __name__ == "__main__":
    #test()
    main()

