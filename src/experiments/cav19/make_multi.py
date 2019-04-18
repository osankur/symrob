import sys
import argparse
import log
import StringIO
from itertools import *

# when set to true, boolean operations are translated as arithmetic ones such as && -> *
numeric_mode = False

# 0 for round-robin
# 1 for EDF
sched_policy = 0

data = [[[5,10,30], [4,8,30]],
        [[5,10,15], [4,8,16]],
        [[10,10,100], [20,20,200]]
       ]

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
from ta import *

class Process:
    def __init__(self, aiger_file_name, index, data_mode=0, factor=1):
        self.index = index
        self.aig = AIG(aiger_file_name, False);
        # [C1,C2,D] where [C1,C2] is the exec time interval, and D relative deadline
        # number of modes is the size of this list
        #self.delays = [[5,10,15], [4,8,16]]
        self.delays = data[data_mode]
        self.delays = map(lambda tab: map(lambda x: factor*x, tab), data[data_mode])
        self.lit_to_formula = dict()
        self._cached_transition = None

    def get_delays(self):
        return self.delays

    def preset1(self):
        # Other [C1,C2,D] values can be set here
        pass

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

    def make_template(self, nmachines):
        def latch_choice(name):
            return "state" in name or "counter" in name
        id = self.index
        latch_list = list(self.aig.iterate_latches())
        latch_locations = dict()

        temp = Template("Process" + str(id))
        # Choose here some latch which should become mode
        clocked_latches = filter(lambda x: latch_choice(self.name_of(x.lit)), latch_list)
        mode_latch = self.name_of(clocked_latches[0].lit) # this is assumed to be non-empty of course

        w = Location("w", initial=True)
        dead = Location("dead")
        rel = Location("rel", committed = True)
        up = Location("up", committed = True)
        disc_up = Location("disc_up", committed=True)
        temp.add_locations([w,dead,rel,up])
        on = [Location("on{0}".format(m)) for m in range(len(self.delays))]
        for m,l in enumerate(on):
            # delay=(c1,c2,d). invariant is that the task finishes before c2
            l.set_invariant("x{0} &lt;= {1}".format(id, self.delays[m][1]))
            temp.add_location(l)

        nmodes = len(self.delays)
        for m,(c1,c2,d) in enumerate(self.delays):
#            mg = "mode{0} == {1}".format(id, m)
            mg = "{0} == {1}".format(mode_latch, m)
            temp.add_transition(Transition(w, on[m], guard=mg, sync="go{0}?".format(id), up="x{0}:=0, w{0}:=0".format(id)))

            # Check deadline miss
            guard="{0} &amp;&amp; x{1} &gt; {2}".format(mg, id, d - c2)
            temp.add_transition(Transition(w,dead,guard=guard))

            # on -> up
            guard = "{0} &amp;&amp; x{1} &gt;= {2} &amp;&amp; x{1} &lt;= {3}".format(mg, id, c1, c2)
            tr = Transition(on[m], up, up="x{0}:=0".format(id), guard=guard)
            temp.add_transition(tr)


        last_location = up
        # Discrete update part
        decl = StringIO.StringIO()
        input_list = list(chain(self.aig.iterate_uncontrollable_inputs(),self.aig.iterate_controllable_inputs()))
        for i in input_list:
            print >> decl, "bool {0};".format(self.name_of(i.lit))
            loc_after_i = Location("JustSet"+self.name_of(i.lit), committed=True)
            tr0 = Transition(last_location, loc_after_i, up="{0} := 0".format(self.name_of(i.lit)))
            tr1 = Transition(last_location, loc_after_i, up="{0} := 1".format(self.name_of(i.lit)))
            temp.add_transition(tr0)
            temp.add_transition(tr1)
            last_location = loc_after_i
            pass

        next_funcs = self.get_next_funcs()
        for xi, x in enumerate(latch_list):
            print >> decl, "bool {0};".format(self.name_of(x.lit))
            latch_locations[x.lit] = Location("Updated"+ self.name_of(x.lit), committed=True)
            up="{0} := {1}".format(self.name_of(x.lit), next_funcs[x.lit])
            temp.add_transition(Transition(last_location, latch_locations[x.lit],up=up))
            last_location = latch_locations[x.lit]

        for j in range(nmachines):
            tr = Transition(last_location, w, guard="running{0} == {1}".format(j, id), sync="release{0}!".format(j), up="w{0}:=1".format(id))
            temp.add_transition(tr)

        temp.set_declaration(decl.getvalue())
        return temp


def powerset(iterable):
    """
    powerset([1,2,3]) --> () (1,) (2,) (3,) (1,2) (1,3) (2,3) (1,2,3)
    """
    xs = list(iterable)
    # note we return an iterator rather than a list
    return chain.from_iterable(combinations(xs,n) for n in range(len(xs)+1))

class Machine:
    def __init__(self, index):
        self.index = index
    def make_template(self, procs):
        # In the round-robin version, there is no test
        # whether a machine is idle
        none = len(procs)-1
        id = self.index
        nb_trans = 0
        nprocs = len(procs)
        temp = Template("Machine" + str(id))

        idle = Location("idle", initial=True, committed=True)
        busy = Location("busy")
        # EDF policy
        if sched_policy == 1:
            temp.add_transition(Transition(busy, idle, sync="release{0}?".format(id), up="running{0} := {1}".format(id,none)))
            temp.add_locations([idle,busy])
            for sel in range(nprocs): # selected process to execute
                for selmode in range(len(procs[sel].delays)): # selected process' mode
                    print >> sys.stderr, "Doing ", sel, " Mode: ", selmode
                    for waits in powerset(range(nprocs)): # for each set of waiting processes
                        nwaits = set(range(nprocs)) - set(waits)
                        wg = "&amp;&amp;".join(map(lambda w: "w{0} == 1".format(w), waits))
                        if not sel in waits:
                            continue
                        waits = list(waits)
                        waits.remove(sel)
                        nwg = "&amp;&amp;".join(map(lambda w: "w{0} == 0".format(w), nwaits))
                        print >> sys.stderr, "\tWaits: ", waits
                        print >> sys.stderr, "\t\t", wg
                        print >> sys.stderr, "\t\t", nwg

                        # Iterate over all possible mode combinations for waits\sel
                        ranges = [range(len(procs[w].delays)) for w in waits]
                        for mode in product(*ranges):
                            print >> sys.stderr, "\t\tModes: ", mode
                            wgc = []
                            for wi, w  in enumerate(waits):
                                # wgc.append("mode{0} == {1} &amp;&amp; {2} &lt;= x{3} - x{0}".format(w, mode[wi], procs[sel].delays[selmode][2] - procs[w].delays[mode[wi]][2], sel))
                                wgc.append("mode{0} == {1} &amp;&amp; x{0} - x{3} &lt;= {2}".format(w, mode[wi], -procs[sel].delays[selmode][2] + procs[w].delays[mode[wi]][2], sel))
                                wgcs = "&amp;&amp;".join(wgc)
                                temp.add_transition(Transition(idle, busy, guard = "&amp;&amp;".join(filter(lambda x: x <> "", [wg, nwg, wgcs])), sync="go{0}!".format(sel), up="running{0} := {1}".format(id, sel)))
                                print >> sys.stderr, "\t\t",wgc
                                nb_trans = nb_trans + 1
        elif sched_policy  == 0: # round-robin
            temp.add_transition(Transition(busy, idle, sync="release{0}?".format(id), up="running{0} := {1}".format(id,none)))
            for pi in range(len(procs)):
                temp.add_transition(Transition(idle,busy,guard="round == {0} &amp;&amp; w{0} == 1".format(pi), sync="go{0}!".format(pi), up="round = {0},  running{1} := {2}".format((pi+1)%len(procs), id, pi)))
                temp.add_transition(Transition(idle,idle,guard="round == {0} &amp;&amp; w{0} == 0".format(pi), up="round = {0}".format((pi+1)%len(procs), id)))
                nb_trans = nb_trans + 2
        # print >> sys.stderr, "Produced", nb_trans, "edges"
        return temp

class TAWRITER:
    def __init__(self, aiger_file_names, data_mode, factor=1):
        self.processes = [Process(x,i,data_mode, factor) for i,x in enumerate(aiger_file_names)]
        self.machines = [Machine(j) for j in range(0,2)]
    """
    Given K, make timed automaton model that restricts each cycle to K time units.
    """
    def get_model(self):
        nta = NTA()
        proc_temps = [p.make_template(len(self.machines)) for p in self.processes]
        mach_temps = [m.make_template(self.processes) for m in self.machines]
        decl = """
chan go0,go1,go2; // Process i can start
chan release0;
chan release1; // Machine j can be freed
int[0,2] running0 = 0; // Machine 1 is running process running1. 3 means none
int[0,2] running1 = 0;

int[0,2] round = 0;
// Is process(i) waiting?
// This is redundant information but don't know how to
// simply access processes' locations
bool w0 = 1;
bool w1 = 1;
bool w2 = 1;

clock x0;
// int[0,1] mode0;

clock x1;
// int[0,1] mode1;

clock x2;
// int[0,1] mode2;
"""
        nta.set_declaration(decl)
        for p in proc_temps:
            nta.add_template(p)
        for m in mach_temps:
            nta.add_template(m)
        nta.set_system("system Process0, Process1, Process2, Machine0, Machine1;")
        nta.dump()

def main():
    parser = argparse.ArgumentParser(description="AIG Format Based Synth")
    parser.add_argument("spec1", metavar="spec1", type=str,
                        help="input specification in extended AIGER format")
    parser.add_argument("spec2", metavar="spec2", type=str,
                        help="input specification in extended AIGER format")
    parser.add_argument("spec3", metavar="spec3", type=str,
                        help="input specification in extended AIGER format")
    parser.add_argument("mode", metavar="mode", type=int,
                        help="index of data set")

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
    tawriter = TAWRITER([args.spec1, args.spec2, args.spec3], args.mode, args.factor)
    tawriter.get_model()

if __name__ == "__main__":
    main()
# add urgency
