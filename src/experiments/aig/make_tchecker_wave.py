import sys
import random
import argparse
import log
from itertools import chain
import StringIO
from ta import *
from dataset import *
numeric_mode = False
# majority, and, or,
# threshold(n,k)


class TAWRITER:
    def __init__(self, graph, time, numeric, bound):
        self.factor=1
        self.delays = []
        self.graph = graph
        self._read_delays(time)
        self.bound = bound
        self.numeric = numeric

    def _read_delays(self, time_file_name):
        with open(time_file_name,'r') as fp:
            all_lines = fp.readlines()
            for s in all_lines:
                if s <> "":
                    si = map(lambda x: int(x), s.split(" "))
                    assert(len(si) == 2)
                    self.delays.append((si[0] * self.factor, si[1] * 2 * self.factor))


    def node_ready(self, node):
        graph = self.graph
        if node[1] == "and" or node[1] == "or":
            inps = node[2]
            g = "_l.out{0} < 2 && _l.out{1} < 2".format(inps[0][0], inps[1][0])
            gn = "(_l.out{0} != 2 &&  _l.out{1} != 2) == 0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "th":
            inps = node[3]
            g =  " && ".join(map(lambda x: "_l.out{0} < 2".format(x[0]), inps))
            gn =  " && ".join(map(lambda x: "(_l.out{0} != 2".format(x[0]), inps)) + ")"*len(inps) + " == 0"
            return (g,gn)
        elif node[1] == "in":
            return ("1==1", "0==1")
        elif node[1] == "not":
            return ("_l.out{0} < 2".format(node[2][0]), "_l.out{0} == 2".format(node[2][0]))
        else:
            raise Exception("unknown gate")

    def node_output_true(self, node):
        if node[1] == "and":
            inps = node[2]
            g = "_l.out{0} == 1 && _l.out{1} == 1".format(inps[0][0], inps[1][0])
            gn = "(_l.out{0} == 1 && _l.out{1} == 1)==0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "or":
            inps = node[2]
            g = "(_l.out{0} == 0 && _l.out{1} == 0) == 0".format(inps[0][0], inps[1][0])
            gn = "_l.out{0} == 0 && _l.out{1} == 0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "th":
            inps = node[3]
            g =  "+".join(map(lambda x: "(_l.out{0}".format(x[0]), inps))+ ")" * len(inps) + " >= {0}".format(node[2])
            gn =  "+".join(map(lambda x: "(_l.out{0}".format(x[0]), inps))+ ")" * len(inps) + " < {0}".format(node[2])
            return (g, gn)
        elif node[1] == "not":
            return ("(1-_l.out{0})==1".format(node[2][0]), "(1-_l.out{0}) ==0".format(node[2][0]))
        if node[1] == "in":
            return ("1==1", "0==1")
        else:
            raise Exception("unknown gate")

    def dump_cyclic_graph(self, bound = None):
        #print >> sys.stderr, self.delays
        graph = self.graph

        print """#include <iostream>
#include "syntax/system.hh"
#include "syntax/sync_product.hh"
namespace wave{
  class layout_t : public syntax::layout_t {
  public:
        """
        for inode,node in enumerate(graph):
            i = node[0]
            print "\tchar out{0};".format(i)
            ins = []
            if node[1] == "and" or node[1] == "or":
                print  "\tchar b{0}_0;".format(i)
                print  "\tchar b{0}_1;".format(i)
            elif node[1] == "th":
                for x in range(len(node[3])):
                    print "\tchar b{0}_{1};".format(i,x)
        print "layout_t() {"
        for inode,node in enumerate(graph):
            i = node[0]
            print "\tout{0} = 2;".format(i)
            if node[1] == "and" or node[1] == "or":
                print "\tb{0}_0 = 2;".format(i)
                print "\tb{0}_1 = 2;".format(i)
            elif node[1] == "th":
                for x in range(len(node[3])):
                    print "\tb{0}_{1} = 2;".format(i,x)
        print """
    }

    virtual ~layout_t() {
    }

    layout_t(const layout_t & l)  = default;

    inline bool operator == (const syntax::layout_t & l) const {
      wave::layout_t const & _l = CAST(wave::layout_t const &, l);
        """
        for inode,node in enumerate(graph):
            i = node[0]
            print "\tif (out{0} != _l.out{0}) return false;".format(i)
            if node[1] == "and" or node[1] == "or":
                print "\tif(b{0}_0 != _l.b{0}_0) return false;".format(i)
                print "\tif(b{0}_1 != _l.b{0}_1) return false;".format(i)
            elif node[1] == "th":
                for x in range(len(node[3])):
                    print "\tif(b{0}_{1} != _l.b{0}_{1}) return false;".format(i,x)
        print """
        return true;
    }

    inline size_t hash() const {
      size_t seed = global_t::instance().hash_seed();
        """
        for inode,node in enumerate(graph):
            i = node[0]
            print "\tboost::hash_combine(seed, out{0});".format(i)
            if node[1] == "and" or node[1] == "or":
                print "\tboost::hash_combine(seed, b{0}_0);".format(i)
                print "\tboost::hash_combine(seed, b{0}_1);".format(i)
            elif node[1] == "th":
                for x in range(len(node[3])):
                    print "\tboost::hash_combine(seed, b{0}_{1});".format(i,x)
        print """
      return seed;
    }

    void output(std::ostream & os) const {
        """
        for inode,node in enumerate(graph):
            i = node[0]
            print "\tos << \"out{0}=\" << out{0} << \",\";".format(i)
            if node[1] == "and" or node[1] == "or":
                print "\tos << \"b{0}_0=\" << b{0}_0 << \",\";".format(i)
                print "\tos << \"b{0}_1=\" << b{0}_1 << \",\";".format(i)
            elif node[1] == "th":
                for x in range(len(node[3])):
                    print "\tos << \"b{0}_1=\" << b{0}_{1} << \",\";".format(i,x)

        print """
    }
  };

}
        """
        print "void build_model(syntax::system_t & s){"
        print "s.name(\"Wave\");"
        print "s.layout_alloc< syntax::layout_T_alloc_t<wave::layout_t> >();"
        print "s.add_clock(\"t\");"
        for inode,node in enumerate(graph):
            i = node[0]
            if node[1] != "in":
                print "s.add_clock(\"x{0}\");".format(i)
        print "s.add_label(\"err\");"
        print "s.add_label(\"unreachable\");"
        for inode,node in enumerate(graph):
            i = node[0]
            ins = []
            if node[1] != "in":
                print "s.add_process(\"Node{0}\");".format(i)
                print "s.add_location(\"Node{0}\", \"down\", \"x{0}<={1}\", \"\", syntax::loc_t::INIT);".format(i, self.delays[i][0])
                print "s.add_location(\"Node{0}\", \"up\", \"x{0}<={1}\", \"\");".format(i,self.delays[i][1])

                #down = Location("down", initial=True)
                #down.set_invariant("x{0} &lt;= {1}".format(i, self.delays[i][0]))
                #up = Location("up")
                #up.set_invariant("x{0} &lt;= {1}".format(i, self.delays[i][1]))

                node_ready = self.node_ready(node)
                node_outputs_true = self.node_output_true(node)

                if bound == None or inode != 0:
                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return {0} && {1};
                    }}
                    """.format(node_ready[0], node_outputs_true[0])
                    up = """
                    [](syntax::layout_t  & l){{
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out{0} = 1;
                    }}
                    """.format(i)
                    print "s.add_edge(\"Node{0}\", \"down\", \"up\", \"x{0}>={1} && x{0}<={2}\", \"\", \"\", {3}, {4});".format(i, self.delays[i][0], self.delays[i][1], disc_g, up)

                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return {0} && {1};
                    }}
                    """.format(node_ready[0], node_outputs_true[1])
                    up = """
                    [](syntax::layout_t  & l){{
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out{0} = 0;
                    }}
                    """.format(i)
                    print "s.add_edge(\"Node{0}\", \"down\", \"up\", \"x{0}>={1} && x{0}<={2}\", \"\", \"\", {3}, {4});".format(i, self.delays[i][0], self.delays[i][1], disc_g, up)


                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return {0};
                    }}
                    """.format(node_ready[1])
                    print "s.add_edge(\"Node{0}\", \"down\", \"down\", \"x{0} == {1}\", \"x{0}\", \"\", {2});".format(i, self.delays[i][0], disc_g)

#                proc.add_transition(Transition(down, down, guard="x{0} == {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[1], up="x{0} := 0".format(i)))

                    up = """
                    [](syntax::layout_t  & l){{
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out{0} = 2;
                    }}
                    """.format(i)
                    print "s.add_edge(\"Node{0}\", \"up\", \"down\", \"x{0} <= {1}\", \"x{0}\", \"\",syntax::layout_true,{2});".format(i, self.delays[i][1], up)


                else:
                    # executed once
                    #print "s.add_clock(\"t\");"
                    guard = "x{0}>={1} && x{0} <= {2} && t <= {3}".format(i, self.delays[i][0], self.delays[i][1], bound)
                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return {0} && {1};
                    }}
                    """.format(node_ready[0], node_outputs_true[0])
                    up = """
                    [](syntax::layout_t  & l){{
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out{0} = 1;
                    }}
                    """.format(i)
                    print "s.add_edge(\"Node{0}\", \"down\", \"up\", \"{1}\", \"\", \"\",{2},{3});".format(i,guard, disc_g, up)
                    #proc.add_transition(Transition(down, up, guard="{1} &lt;= x{0} &amp;&amp; x{0} &lt;= {2}".format(i, self.delays[i][0], self.delays[i][1]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[0] + bg, up="out{0} := 1".format(i)))
                    print "s.add_edge(\"Node{0}\", \"down\", \"down\", \"t>{1}\", \"\", \"\", syntax::layout_true, [](syntax::layout_t  & l){{wave::layout_t & _l = CAST(wave::layout_t &, l);".format(i, bound)
                    for n in filter(lambda n: n[1] != "in", graph):
                        print("_l.out{0} = 2;\n".format(n[0]))
                    print """
                    });
                    """
                    # this is new
#                    proc.add_transition(Transition(down,down, guard="t &gt; {0}".format(bound), up=non_input_out_reset))

                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return {0} && {1};
                    }}
                    """.format(node_ready[0], node_outputs_true[1])
                    up = """
                    [](syntax::layout_t  & l){{
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out{0} = 0;
                    }}
                    """.format(i)
                    print "s.add_edge(\"Node{0}\", \"down\", \"up\", \"x{0}>={1} && x{0}<={2}\", \"\", \"\", {3}, {4});".format(i, self.delays[i][0], self.delays[i][1], disc_g, up)

#                proc.add_transition(Transition(down, up, guard="{1} &lt;= x{0} &amp;&amp; x{0} &lt;= {2} ".format(i, self.delays[i][0], self.delays[i][1]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[1], up="out{0} := 0".format(i)))


                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return {0};
                    }}
                    """.format(node_ready[1])
                    print "s.add_edge(\"Node{0}\", \"down\", \"down\", \"x{0} == {1}\", \"x{0}\", \"\", {2});".format(i, self.delays[i][0], disc_g)

#                proc.add_transition(Transition(down, down, guard="x{0} == {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[1], up="x{0} := 0".format(i)))

                    up = """
                    [](syntax::layout_t  & l){{
                       wave::layout_t & _l = CAST(wave::layout_t &, l);
                       _l.out{0} = 2;
                    }}
                    """.format(i)

                    print "s.add_edge(\"Node{0}\", \"up\", \"down\", \"x{0} <= {1}\", \"x{0}\", \"\",syntax::layout_true,{2});".format(i, self.delays[i][1],up)
#                proc.add_transition(Transition(up, down, guard="x{0} &lt;={1}".format(i, self.delays[i][1]), up="x{0}:=0".format(i)))

                if inode == 0:
                    disc_g = """
                    [](syntax::layout_t const & l){{
                       wave::layout_t const & _l = CAST(wave::layout_t const &, l);
                       return _l.out{0};
                    }}
                    """.format(i)
                    print "s.add_location(\"Node{0}\", \"err\", \"\", \"err\");".format(i)
                    print "s.add_edge(\"Node{0}\", \"up\", \"err\", \"\", \"\", \"\", {1});".format(i, disc_g)
#                    proc.add_transition(Transition(up,Location("err"), guard="out{0}==1".format(i)))
        input_nodes = filter(lambda n: n[1] == "in", graph)
        print "s.add_process(\"input\");"
        print "s.add_location(\"input\",\"input_init\",\"\",\"\",syntax::loc_t::INIT | syntax::loc_t::COMMITTED);"
        prev_loc = "input_init"
        for node in input_nodes:
            print "s.add_location(\"input\",\"in{0}\",\"\",\"\",syntax::loc_t::COMMITTED);".format(node[0])
        for node in input_nodes:
            i = node[0]
            up0 = """
            [](syntax::layout_t  & l){{
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out{0} = 0;
            }}
            """.format(i)
            up1 = """
            [](syntax::layout_t  & l){{
            wave::layout_t & _l = CAST(wave::layout_t &, l);
            _l.out{0} = 1;
            }}
            """.format(i)

            print "s.add_edge(\"input\", \"{2}\", \"in{0}\",\"\", \"\",\"\",syntax::layout_true,{1});".format(i,up0,prev_loc)
            print "s.add_edge(\"input\", \"{2}\", \"in{0}\",\"\", \"\",\"\",syntax::layout_true,{1});".format(i,up1,prev_loc)
            prev_loc = "in{0}".format(i)
        print "s.add_location(\"input\",\"input_end\");"
        print "s.add_edge(\"input\", \"{0}\", \"input_end\");".format(prev_loc)
        print "\ts.synchronizer<syntax::asynchronous_product_t>();\n}"


def main():
    global numeric_mode
    parser = argparse.ArgumentParser(description="Wave Benchmark generator")
    parser.add_argument("time", metavar="time", type=str,
                        help="input file for time intervals")
    parser.add_argument("-v", "--verbose_level", dest="verbose_level",
                        default="", required=False,
                        help="Verbose level = (D)ebug, (W)arnings, " +
                             "(L)og messages, (B)DD dot dumps")
    parser.add_argument("-n", "--numeric", action="store_true",
                        help=("Encode Boolean functions with number operations"))
    parser.add_argument("-b", "--bound", type=int,
                        help=("Time bound before the output node becomes 1"))
    args = parser.parse_args()
    log.parse_verbose_level(args.verbose_level)
    out_dir = "/tmp/"
    # realizability / synthesis
    for i,gr in enumerate(graph):
        if gr == None:
            continue
        tawriter = TAWRITER(gr, args.time, args.numeric, 3000)
        with open("{0}a{1}.cpp".format(out_dir,i),"w") as f:
            sys.stdout = f
        # tawriter.test();
        # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
        # tawriter.dump_model(args.clocked_latches, args.bound)
            tawriter.dump_cyclic_graph(args.bound)
    for i,gr in enumerate(graph_sat):
        if gr == None:
            continue
        tawriter = TAWRITER(gr, args.time, args.numeric, 3000)
        with open("{0}b{1}.cpp".format(out_dir, i),"w") as f:
            sys.stdout = f
        # tawriter.test();
        # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
        # tawriter.dump_model(args.clocked_latches, args.bound)
            tawriter.dump_cyclic_graph(args.bound)

if __name__ == "__main__":
    main()
    #dump_graph(graph1)
