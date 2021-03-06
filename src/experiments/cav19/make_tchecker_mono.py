"""
Given an AIG file and a time configuration file TIME which contains a pair of integers for each latch. The TAWRITER class constructs a timed automaton which simulates this circuit with the following timing constraints.
For each latch, we are given the pair (delay[0],delay[1]). The circuit simulation can perform a new cycle if only if for each latch l:
- if l is about to change from 1 to 0, then at least delay[0] time units have passed since the value was changed to 1
- if l is about to change from 0 to 1, then at least delay[1] time units have passed since the value was changed to 0
If the value of l does not change, then there is no time constraint.

The present version computes an urgent model where each cycle is executed as soon as possible.
A deadlock is present iff there is a deadlock in the model (in the sense of Uppaal) or
location "dead" is reachable.

Latch names are obtained by replacing <, > characters by _ and by prefixing them by L
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

# when set to true, boolean operations are translated as arithmetic ones such as && -> *
numeric_mode = False

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
                #print "Doing line:<{0}>".format(s)
                #print s.split(" ")
                    si = map(lambda x: int(x), s.split(" "))
                    assert(len(si) == 2)
                    delays[latches[l]] = (si[0] * self.factor,si[1] * self.factor)
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
        #print >> sys.stderr, "lit", lit, (input,latch,and_gate)
        if latch:
            return "L"+self.aig.get_lit_name(lit).replace("<", "_").replace(">", "_");
        elif input:
            # Boolean variables are encoded as 1-bit integers for now
            return "I"+self.aig.get_lit_name(lit).replace("<", "_").replace(">", "_");
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
            result = "(_l.{0})".format(self.name_of(stripped_lit))
        elif and_gate:
            if numeric_mode:
                result = ("({0} * {1})".format(self.lit2formula(and_gate.rhs0),
                      self.lit2formula(and_gate.rhs1)))
            else:
                result = ("({0} && {1})".format(self.lit2formula(and_gate.rhs0),
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

    def make_discrete_guard(self, g):
        return """
        [](syntax::layout_t const & l){{\\
        monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);\\
        return {0};\\
        }}
        """.format(g)

    def make_discrete_update(self, u):
        return """ [](syntax::layout_t  & l){{\\
                       monoprocess::layout_t & _l = CAST(monoprocess::layout_t &, l);\\
                       {0};\\
                    }}
                    """.format(u)

    """
    Given K, make timed automaton model that restricts each cycle to K time units.
    """
    def get_cycle_time_model(self, nb_clocked_latches, K):
        K = self.factor * K
        latch_locations = dict()
        # clock name associated to given lit which is a latch
        clock_name = dict()
        input_list = list(chain(self.aig.iterate_uncontrollable_inputs(),self.aig.iterate_controllable_inputs()))
        latch_list = list(self.aig.iterate_latches())
        latch_num = len(latch_list)

        clocked_latches = filter(lambda x: "state" in self.name_of(x.lit), latch_list)
        clocked_latches = latch_list
        clocked_latches = clocked_latches[0:nb_clocked_latches]
 
        print """#include <iostream>
        #include "syntax/system.hh"
        #include "syntax/sync_product.hh"
        namespace monoprocess {
        class layout_t : public syntax::layout_t {
        public:
        """
        for i in input_list:
            print "\tbool {0};".format(self.name_of(i.lit))
        for x in latch_list:
            print "\tbool {0};".format(self.name_of(x.lit))

        print "\tlayout_t(){"
        for i in input_list:
            print "\t\t{0} = 0;".format(self.name_of(i.lit))
        for x in latch_list:
            print "\t\t{0} = 0;".format(self.name_of(x.lit))
        print "\t}\nvirtual ~layout_t(){}";
        print "layout_t (const layout_t &l) = default;"
        print """
        inline bool operator == (const syntax::layout_t & l) const {
            monoprocess::layout_t const & _l = CAST(monoprocess::layout_t const &, l);
        """
        for i in input_list:
            print "\t\tif({0} != _l.{0}) return false;".format(self.name_of(i.lit))
        for x in latch_list:
            print "\t\tif({0} != _l.{0}) return false;".format(self.name_of(x.lit))
        print "return true;\n}"

        print """
        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        """
        for i in input_list + latch_list:
            print "\t\tboost::hash_combine(seed, {0});".format(self.name_of(i.lit))
        print "return seed;\n}"

        print """
        void output(std::ostream & os) const {
        """
        for i in input_list + latch_list:
            print "\t\tos << \"{0} = \" << {0} << \",\";".format(self.name_of(i.lit))
        print "\t}\n};\n}"

        print """void build_model(syntax::system_t & s){
        \ts.name(\"Mono\");
        \ts.layout_alloc< syntax::layout_T_alloc_t<monoprocess::layout_t> >();
        """
        for x in clocked_latches:
            clock_name[x.lit] = "x_" + str(x.lit)
            print "s.add_clock(\"{0}\");".format(clock_name[x.lit])
        print "s.add_clock(\"T\");"
        print "s.add_label(\"err\");"
        print "s.add_label(\"nothing\");"
        print "s.add_process(\"Circuit\");"

        print "s.add_location(\"Circuit\", \"init\", \"\", \"\", syntax::loc_t::INIT | syntax::loc_t::URGENT);"
        #init = Location("Init", urgent=True,initial=True)
        print "s.add_location(\"Circuit\", \"dead\", \"\", \"err\");"
        #deadlock = Location("dead")

        # nta.set_query("E<>Process.dead")
        # for x in self.aig.iterate_latches():
        last_location = "init"
        for i in input_list:
            loc_after_i = "JustSet"+self.name_of(i.lit)
            print "s.add_location(\"Circuit\", \"{0}\", \"\", \"\", syntax::loc_t::URGENT);".format(loc_after_i)
            #loc_after_i = Location("JustSet"+self.name_of(i.lit), urgent=True)
            #tr0 = Transition(last_location, loc_after_i, up="{0} := 0".format(self.name_of(i.lit)))
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"\", \"\", \"\", syntax::layout_true,".format(last_location, loc_after_i)
            print self.make_discrete_update("_l.{0}=0;".format(self.name_of(i.lit)))
            print ");"
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"\", \"\", \"\", syntax::layout_true,".format(last_location, loc_after_i)
            print self.make_discrete_update("_l.{0}=1;".format(self.name_of(i.lit)))
            print ");"

            #tr1 = Transition(last_location, loc_after_i, up="{0} := 1".format(self.name_of(i.lit)))
            #temp.add_transition(tr0)
            #temp.add_transition(tr1)
            last_location = loc_after_i

        next_funcs = self.get_next_funcs()

        for x in latch_list:
            #print >> decl, "bool {0};".format(self.name_of(x.lit))
            if not x in clocked_latches:
                continue
            #latch_locations[x.lit] = Location("Updated"+ self.name_of(x.lit), urgent=True)
            latch_locations[x.lit] = "Updated"+ self.name_of(x.lit)
            print "s.add_location(\"Circuit\", \"{0}\", \"\", \"\", syntax::loc_t::URGENT);".format(latch_locations[x.lit])

            # if the value does not change:
            #g = "{0} == {1}".format(self.name_of(x.lit), next_funcs[x.lit])
            #tr = Transition(last_location, latch_locations[x.lit], guard=g)
            #temp.add_transition(tr)
            disc_g = self.make_discrete_guard("_l.{0}=={1};".format(self.name_of(x.lit), next_funcs[x.lit]))
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"\", \"\", \"\", {2});".format(last_location, latch_locations[x.lit], disc_g)

            # if it changes but the delay is already respected, move on directly
            # g = "{0} == 1 &amp;&amp; {0} != {1} &amp;&amp; {2} &gt;= {3}".format(self.name_of(x.lit), next_funcs[x.lit], clock_name[x.lit], self.delays[x.lit][0])
            # temp.add_transition(Transition(last_location, latch_locations[x.lit], guard=g))

            disc_g = self.make_discrete_guard("_l.{0} == 1 && _l.{0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit]))
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"{2} <= {3}\", \"\", \"\", {4});".format(last_location, latch_locations[x.lit], clock_name[x.lit], self.delays[x.lit][0], disc_g)


            disc_g = self.make_discrete_guard("_l.{0} == 0 && _l.{0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit]))
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"{2} <= {3}\", \"\", \"\", {4});".format(last_location, latch_locations[x.lit], clock_name[x.lit], self.delays[x.lit][1], disc_g)

            # if we have to wait to respect the delay go to specific wait state and wait precisely for the delay (matching invariant + guard)
            loc0 = latch_locations[x.lit] + "_becomes0"
            print "s.add_location(\"Circuit\", \"{0}\",\"{1}<={2}\", \"\");".format(loc0,clock_name[x.lit], self.delays[x.lit][0])
            #loc0.set_invariant("{1} <= {2}".format()
            loc1 = latch_locations[x.lit] + "_becomes1"
            #loc1.set_invariant("{0} &lt;= {1}".format(clock_name[x.lit], self.delays[x.lit][1]))
            print "s.add_location(\"Circuit\", \"{0}\",\"{1}<={2}\", \"\");".format(loc1,clock_name[x.lit], self.delays[x.lit][1])

#            g = "{0} == 1 &amp;&amp; {0} != {1} &amp;&amp; {2} &lt; {3}".format(self.name_of(x.lit), next_funcs[x.lit], clock_name[x.lit], self.delays[x.lit][0])
            disc_g = self.make_discrete_guard("_l.{0} == 1 && _l.{0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit]))
            g =  "{0} < {1}".format(clock_name[x.lit], self.delays[x.lit][0])
            #tr = Transition(last_location, loc0, guard=g)
            #temp.add_transition(tr)
            if self.delays[x.lit][0] > 0:
                print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"{2}\", \"\", \"\", {3});".format(last_location,loc0, g, disc_g)


            up=self.make_discrete_update("_l.{0} = {1};".format( self.name_of(x.lit), next_funcs[x.lit]))
#            up="{0}:=0, {1} := {2}".format(clock_name[x.lit], self.name_of(x.lit), next_funcs[x.lit])
            g = "{0} >= {1}".format(clock_name[x.lit], self.delays[x.lit][0])
            #tr = Transition(loc0, latch_locations[x.lit], guard=g, up=up)
            #temp.add_transition(tr)
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"{2}\", \"{3}\", \"\", syntax::layout_true, {4});".format(loc0, latch_locations[x.lit], g, clock_name[x.lit], up)

#            g = "{0} == 0 &amp;&amp; {0} != {1} &amp;&amp; {2} &lt; {3}".format(self.name_of(x.lit), next_funcs[x.lit], clock_name[x.lit], self.delays[x.lit][1])
#            tr = Transition(last_location, loc1, guard=g)
#            temp.add_transition(tr)
            g = "{0} < {1}".format(clock_name[x.lit], self.delays[x.lit][1])
            if self.delays[x.lit][1] > 0:
                disc_g = self.make_discrete_guard("_l.{0} == 0 && _l.{0} != {1}".format(self.name_of(x.lit), next_funcs[x.lit]))
                print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"{2}\", \"\", \"\", {3});".format(last_location, loc1, g, disc_g)

            up = self.make_discrete_update("_l.{0} = {1};".format(self.name_of(x.lit), next_funcs[x.lit]))
            #g = "{0} &gt;= {1}".format(clock_name[x.lit], self.delays[x.lit][1])
            g = "{0} >= {1}".format(clock_name[x.lit], self.delays[x.lit][1])
            print "s.add_edge(\"Circuit\", \"{0}\", \"{1}\", \"{2}\", \"{3}\", \"\", syntax::layout_true, {4});".format(loc1, latch_locations[x.lit], g, clock_name[x.lit], up)
            #tr = Transition(loc1, latch_locations[x.lit], guard=g, up=up)
            #temp.add_transition(tr)

            last_location = latch_locations[x.lit]
        #go_deadlock=Transition(last_location, deadlock, guard="T &gt;{0}".format(str(K)))
        print "s.add_edge(\"Circuit\", \"{0}\", \"dead\", \"T>{1}\", \"\", \"\", syntax::layout_true);".format(last_location, str(K))
        print "s.add_edge(\"Circuit\", \"{0}\", \"init\", \"T<={1}\", \"T\", \"\", syntax::layout_true);".format(last_location, str(K))

        print "s.synchronizer<syntax::asynchronous_product_t>();\n}"
        #come_back= Transition(last_location, init, guard="T &lt;= {0}".format(str(K)), up="T:=0")
        #temp.add_transition(come_back)
        #temp.add_transition(go_deadlock)
        #last_location = init
        #nta.set_declaration(decl.getvalue())
        #nta.dump()

def main():
    global numeric_mode
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
    parser.add_argument("-n", "--numeric", action="store_true",
                        help=("Encode Boolean functions with number operations"))
    args = parser.parse_args()
    log.parse_verbose_level(args.verbose_level)
    numeric_mode = args.numeric
    # realizability / synthesis
    tawriter = TAWRITER(args.spec, args.time, args.factor)
    # tawriter.test();
    # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
    tawriter.get_cycle_time_model(args.clocked_latches, args.bound)

if __name__ == "__main__":
    main()
