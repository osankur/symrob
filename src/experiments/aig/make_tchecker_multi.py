"""
TODO: Add latches and take the state space into account
"""
import sys
import argparse
import log
import StringIO
from itertools import *

# when set to true, boolean operations are translated as arithmetic ones such as && -> *
numeric_mode = True

# 0 for round-robin
# 1 for EDF
sched_policy = 0

data = [[[5,10,30], [4,8,30]],
        [[5,10,15], [4,8,16]],
        [[10,10, 100], [20,20, 200]]
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


def make_discrete_guard(g):
    return """
    [](syntax::layout_t const & l){{\\
    multi::layout_t const & _l = CAST(multi::layout_t const &, l);\\
    return {0};\\
    }}
    """.format(g)

def make_discrete_update(u):
    return """ [](syntax::layout_t  & l){{\\
    multi::layout_t & _l = CAST(multi::layout_t &, l);\\
    {0};\\
    }}
    """.format(u)


class Process:
    def __init__(self, aiger_file_name, index, data_mode=0, factor=1):
        self.index = index
        self.aig = AIG(aiger_file_name, False);
        # [C1,C2,D] where [C1,C2] is the exec time interval, and D relative deadline
        # number of modes is the size of this list
#        self.delays = [[5,10,15], [4,8,16]]
        self.delays = map(lambda tab: map(lambda x: factor*x, tab), data[data_mode])
        self.lit_to_formula = dict()
        self._cached_transition = None
        self.input_list = list(chain(self.aig.iterate_uncontrollable_inputs(),self.aig.iterate_controllable_inputs()))
        self.latch_list = list(self.aig.iterate_latches())


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
        ident = "P"+str(self.index)
        (intput, latch, and_gate) = self.aig.get_lit_type(lit)
        # is it an input, latch, gate or constant
        #print >> sys.stderr, "lit", lit, (input,latch,and_gate)
        if latch:
            return "L"+ident+self.aig.get_lit_name(lit).replace("<", "_").replace(">", "_");
        elif input:
            # Boolean variables are encoded as 1-bit integers for now
            return "I"+ident+self.aig.get_lit_name(lit).replace("<", "_").replace(">", "_");
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

    def dump(self, nmachines):
        def latch_choice(name):
            return "state" in name or "counter" in name
        input_list = self.input_list
        latch_list = self.latch_list
        id = self.index

        latch_locations = dict()
        print "s.add_process(\"Process{0}\");".format(id)
        pr = "\"Process{0}\"".format(id)
        # Choose here some latch which should become mode
        clocked_latches = filter(lambda x: latch_choice(self.name_of(x.lit)), latch_list)
        mode_latch = self.name_of(clocked_latches[0].lit) # this is assumed to be non-empty of course

        # w = Location("w", initial=True)
        # dead = Location("dead", error=True)
        # rel = Location("rel", committed = True)
        # up = Location("up", committed = True)
        #disc_up = Location("disc_up", committed=True)
        print "s.add_location({0}, \"w\", \"\", \"\", syntax::loc_t::INIT);".format(pr)
        print "s.add_location({0}, \"dead\", \"\", \"err\");".format(pr)
        print "s.add_location({0}, \"rel\", \"\", \"\", syntax::loc_t::COMMITTED);".format(pr)
        print "s.add_location({0}, \"up\", \"\", \"\", syntax::loc_t::COMMITTED);".format(pr)
        print "s.add_location({0}, \"disc_up\", \"\", \"\", syntax::loc_t::COMMITTED);".format(pr)

        for m in range(len(self.delays)):
            print "s.add_location({0}, \"on{1}\", \"x{2} <= {3}\",\"\");".format(pr, m, id, self.delays[m][1])
        #on = [Location("on{0}".format(m)) for m in range(len(self.delays))]
        #for m,l in enumerate(on):
        #    # delay=(c1,c2,d). invariant is that the task finishes before c2
        #    l.set_invariant("x{0} &lt;= {1}".format(id, self.delays[m][1]))
        #    temp.add_location(l)


        nmodes = len(self.delays)
        for m,(c1,c2,d) in enumerate(self.delays):
#            mg = "mode{0} == {1}".format(id, m)
            mg = make_discrete_guard("_l.{0} == {1}".format(mode_latch, m))
            up = make_discrete_update("_l.w{0} = 0".format(id))
#            temp.add_transition(Transition(w, on[m], disc_guard=mg, sync="go{0}?".format(id), disc_up="w{0}=0;".format(id), reset="x{0}".format(id)))
            print "s.add_edge({0}, \"w\", \"on{1}\", \"\", \"x{2}\", \"go{2}?\", {3}, {4});".format(pr, m, id, mg, up)

            # Check deadline miss
            g="x{0} >= {1}".format(id, d - c2-1)
            up=make_discrete_update("_l.dead=1;")
            #temp.add_transition(Transition(w,dead,disc_guard=mg, disc_up="dead=1;",guard=guard))
            print "s.add_edge({0}, \"w\", \"dead\", \"{1}\", \"\", \"\", {2}, {3});".format(pr, g , mg, up)

            # on -> up
            #guard = "x{1} &gt;= {2} &amp;&amp; x{1} &lt;= {3}".format(mg, id, c1, c2)
            #tr = Transition(on[m], up, reset="x{0}".format(id), disc_guard=mg, guard=guard)
            #temp.add_transition(tr)
            guard = "x{1} >= {2} && x{1} <= {3}".format(mg, id, c1, c2)
            print "s.add_edge({0}, \"on{1}\", \"up\", \"{2}\", \"x{3}\", \"\", {4});".format(pr, m, guard, id, mg)


        last_location = "up"
        # Discrete update part
        for i in input_list:
            # print >> decl, "var {0} :".format(self.name_of(i.lit))+"{0..1}=0;"
            loc_after_i = "JustSet"+self.name_of(i.lit)
            print "s.add_location({0}, \"{1}\", \"\", \"\", syntax::loc_t::COMMITTED);".format(pr, loc_after_i)
            print "s.add_edge({0}, \"{1}\", \"{2}\", \"\", \"\", \"\", syntax::layout_true, {3});".format(pr, last_location, loc_after_i, make_discrete_update("_l.{0} = 0;".format(self.name_of(i.lit))))
            print "s.add_edge({0}, \"{1}\", \"{2}\", \"\", \"\", \"\", syntax::layout_true, {3});".format(pr, last_location, loc_after_i, make_discrete_update("_l.{0} = 1;".format(self.name_of(i.lit))))
            #tr0 = Transition(last_location, loc_after_i, disc_up="{0} = 0;".format(self.name_of(i.lit)))
            #tr1 = Transition(last_location, loc_after_i, disc_up="{0} = 1;".format(self.name_of(i.lit)))
            #temp.add_transition(tr0)
            #temp.add_transition(tr1)
            last_location = loc_after_i
            pass

        next_funcs = self.get_next_funcs()
        for xi, x in enumerate(latch_list):
            #print >> decl, "var {0} :".format(self.name_of(x.lit))+"{0..1}=0;"
            latch_locations[x.lit] = "Updated"+ self.name_of(x.lit)
            print "s.add_location({0}, \"{1}\", \"\", \"\", syntax::loc_t::COMMITTED);".format(pr, latch_locations[x.lit])

            disc_up=make_discrete_update("_l.{0} = {1};".format(self.name_of(x.lit), next_funcs[x.lit]))
            #temp.add_transition(Transition(last_location, latch_locations[x.lit],disc_up=disc_up))
            print "s.add_edge({0}, \"{1}\", \"{2}\", \"\", \"\", \"\", syntax::layout_true, {3});".format(pr, last_location, latch_locations[x.lit], disc_up)
            last_location = latch_locations[x.lit]

        for j in range(nmachines):
            up = make_discrete_update("_l.w{0} = 1;".format(id))
            dg = make_discrete_guard("_l.running{0} == {1}".format(j, id))
            print "s.add_edge({0}, \"{1}\", \"w\", \"\", \"\", \"release{2}!\", {3}, {4});".format(pr, last_location, j, dg, up)
            #tr = Transition(last_location, w, disc_guard="running{0} == {1}".format(j, id), sync="release{0}!".format(j), disc_up="w{0}=1".format(id))
            #temp.add_transition(tr)


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
    def dump(self, procs):
        # In the round-robin version, there is no test
        # whether a machine is idle
        none = len(procs)-1
        id = self.index
        nb_trans = 0
        nprocs = len(procs)

        print "s.add_process(\"Machine{0}\");".format(id)
        pr = "\"Machine{0}\"".format(id)

        print "s.add_location({0}, \"idle\", \"\", \"\", syntax::loc_t::COMMITTED | syntax::loc_t::INIT);".format(pr)
        print "s.add_location({0}, \"busy\", \"\",\"\");".format(pr)
        #idle = Location("idle", initial=True, committed=True)
        #busy = Location("busy")
        # EDF policy
        if sched_policy  == 0: # round-robin
            #temp.add_transition(Transition(busy, idle, sync="release{0}?".format(id), disc_up="running{0} = {1};".format(id,none)))
            print "s.add_edge({0}, \"busy\", \"idle\", \"\", \"\", \"release{1}?\", syntax::layout_true, {2});".format(pr, id, make_discrete_update("_l.running{0} = {1};".format(id, none)))
            for pi in range(len(procs)):
                #temp.add_transition(Transition(idle,busy,disc_guard="round == {0} &amp;&amp; w{0} == 1".format(pi), sync="go{0}!".format(pi), disc_up="round = {0};  running{1} = {2};".format((pi+1)%len(procs), id, pi)))
                up = make_discrete_update("_l.round = {0}; _l.running{1} = {2}; /*here?*/".format((pi+1)%len(procs), id, pi))
                dg = make_discrete_guard("_l.round == {0} && _l.w{0} == 1".format(pi))
                print "s.add_edge({0}, \"idle\", \"busy\", \"\", \"\", \"go{1}!\", {2}, {3});".format(pr,pi, dg, up);

                up = make_discrete_update("_l.round = {0};".format((pi+1)%len(procs)))
                dg = make_discrete_guard("_l.round == {0} && _l.w{0} == 0".format(pi))
                print "s.add_edge({0}, \"idle\", \"idle\", \"\", \"\", \"\", {2}, {3});".format(pr,pi, dg, up);
                #temp.add_transition(Transition(idle,idle,disc_guard="round == {0} &amp;&amp; w{0} == 0".format(pi), disc_up="round = {0};".format((pi+1)%len(procs), id)))
                nb_trans = nb_trans + 2
        else:
            raise Exception("EDF not implemented")

class TAWRITER:
    def __init__(self, aiger_file_names, data_mode, factor=1):
        self.processes = [Process(x,i,data_mode, factor) for i,x in enumerate(aiger_file_names)]
        self.machines = [Machine(j) for j in range(0,2)]
    """
    Given K, make timed automaton model that restricts each cycle to K time units.
    """
    def get_model(self):
#        proc_temps = [p.make_template(len(self.machines), decl) for p in self.processes]
#        mach_temps = [m.make_template(self.processes) for m in self.machines]
        proc_temps = self.processes
        mach_temps = self.machines

        print """#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace multi{
  class layout_t : public syntax::layout_t {
  public:
        """
        for p in proc_temps:
            for i in p.input_list:
                print "bool {0};".format(p.name_of(i.lit))
            for x in p.latch_list:
                print "bool {0};".format(p.name_of(x.lit))
        # TODO Add machine variables
        print """
        char running0;
        char running1;
        char dead ;
        char round ;
        bool w0 ;
        bool w1 ;
        bool w2 ;
    layout_t(){
        """
        for p in proc_temps:
            for i in p.input_list:
                print "{0} ".format(p.name_of(i.lit))+"=0;"
            for x in p.latch_list:
                print "{0} ".format(p.name_of(x.lit))+"=0;"
        print """
        running0 = 0;
        running1 = 0;
        dead = 0;
        round = 0;
        w0 = 1;
        w1 = 1;
        w2 = 1;
    }
    virtual ~layout_t() {
    }

    layout_t(const layout_t & l)  = default;
    inline bool operator == (const syntax::layout_t & l) const {
      multi::layout_t const & _l = CAST(multi::layout_t const &, l);
        """
        for p in proc_temps:
            for i in p.input_list:
                print "if (_l.{0} != {0}) return false;".format(p.name_of(i.lit))
            for x in p.latch_list:
                print "if (_l.{0} != {0}) return false;".format(p.name_of(x.lit))
            print """
            if (_l.running0 != running0) return false;
            if (_l.running1 != running1) return false;
            if (_l.round != round) return false;
            if (_l.w0 != w0) return false;
            if (_l.w1 != w1) return false;
            if (_l.w2 != w2) return false;
            if (_l.dead != dead) return false;
            """
        print """return true;\n}
        inline size_t hash() const {
        size_t seed = global_t::instance().hash_seed();
        """
        for p in proc_temps:
            for i in p.input_list:
                print "\tboost::hash_combine(seed,{0});".format(p.name_of(i.lit))
            for x in p.latch_list:
                print "\tboost::hash_combine(seed,{0});".format(p.name_of(x.lit))
            print """
            \tboost::hash_combine(seed, running0);
            \tboost::hash_combine(seed, running1);
            \tboost::hash_combine(seed, round);
            \tboost::hash_combine(seed, w0);
            \tboost::hash_combine(seed, w1);
            \tboost::hash_combine(seed, w2);
            \tboost::hash_combine(seed, dead);
            """
        print "return seed;\n}\n"
        print "void output(std::ostream & os) const {}"
        print "};\n}";

        print "void build_model(syntax::system_t & s){"
        print "s.name(\"Multi\");"
        print "s.layout_alloc< syntax::layout_T_alloc_t<multi::layout_t> >();"
        for p in proc_temps:
            print "s.add_clock(\"x{0}\");".format(p.index)
        print "s.add_label(\"err\");"
        for p in proc_temps:
            p.dump(len(self.machines))
        for m in mach_temps:
            m.dump(self.processes)
        print "auto & sp = s.synchronizer<syntax::synchronized_product_t>(s);"
        for p in range(len((proc_temps))):
            for m in range(len((mach_temps))):
                print "sp.add_sync(\"Process{0}.release{1}!,Machine{1}.release{1}?\");".format(p,m)
                print "sp.add_sync(\"Process{0}.go{0}?,Machine{1}.go{0}!\");".format(p,m)
        print "}"

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
    parser.add_argument("-o", "--out_file", dest="out_file", type=str,
                        required=False, default=None,
                        help=("Output file path. If file extension = .aig, " +
                              "binary output format will be used, if " +
                              "file extension = .aag, ASCII output will be " +
                              "used. The argument is ignored if the spec is " +
                              "not realizable."))
    parser.add_argument("-f", "--factor", dest="factor", type=int,
                        required=False, default=1,
                        help=("Factor by which all constants are to be multiplied"))
    args = parser.parse_args()
    log.parse_verbose_level(args.verbose_level)
    # realizability / synthesis
    tawriter = TAWRITER([args.spec1, args.spec2, args.spec3], args.mode, args.factor)
    # tawriter.test();
    # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
    tawriter.get_model()

if __name__ == "__main__":
    main()
# add urgency
