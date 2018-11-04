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
                    self.delays.append((si[0] * self.factor,si[0] * 2 * self.factor))


    def node_ready(self, node):
        graph = self.graph
        if node[1] == "and" or node[1] == "or":
            inps = node[2]
            g = "out{0} &lt; 2 &amp;&amp; out{1} &lt; 2".format(inps[0][0], inps[1][0])
            gn = "(out{0} != 2 &amp;&amp; out{1} != 2) == 0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "th":
            inps = node[3]
            g =  " &amp;&amp; ".join(map(lambda x: "out{0} &lt; 2".format(x[0]), inps))
            gn =  " &amp;&amp; ".join(map(lambda x: "(out{0} != 2".format(x[0]), inps)) + ")"*len(inps) + " == 0"
            return (g,gn)
        elif node[1] == "in":
            return ("1==1", "0==1")
        elif node[1] == "not":
            return ("out{0}&lt;2".format(node[2][0]), "out{0}&lt;2".format(node[2][0]))
        else:
            raise Exception("unknown gate")

    def node_output_true(self, node):
        if node[1] == "and":
            inps = node[2]
            g = "out{0} == 1 &amp;&amp; out{1} == 1".format(inps[0][0], inps[1][0])
            gn = "(out{0} == 1 &amp;&amp; out{1} == 1)==0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "or":
            inps = node[2]
            g = "(out{0} == 0 &amp;&amp; out{1} == 0) == 0".format(inps[0][0], inps[1][0])
            gn = "out{0} == 0 &amp;&amp; out{1} == 0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "th":
            inps = node[3]
            g =  "+".join(map(lambda x: "(out{0}".format(x[0]), inps))+ ")" * len(inps) + " &gt;= {0}".format(node[2])
            gn =  "+".join(map(lambda x: "(out{0}".format(x[0]), inps))+ ")" * len(inps) + " &lt; {0}".format(node[2])
            return (g, gn)
        elif node[1] == "not":
            return ("(1-out{0})==1".format(node[2][0]), "(1-out{0}) ==0".format(node[2][0]))
        if node[1] == "in":
            return ("1==1", "0==1")
        else:
            raise Exception("unknown gate")

    def dump_cyclic_graph(self, bound = None):
        #print >> sys.stderr, self.delays
        graph = self.graph


        nta = NTA()
        decl = StringIO.StringIO()

        for inode,node in enumerate(graph):
            i = node[0]
            print >> decl, "int[0,2] out{0} = 2;".format(i)
            ins = []
            if node[1] == "and" or node[1] == "or":
                print >> decl, "int[0,2] b{0}_0 = 2;".format(i)
                print >> decl, "int[0,2] b{0}_1 = 2;".format(i)
            elif node[1] == "th":
                for x in range(len(node[3])):
                    print >> decl, "int[0,2] b{0}_{1} = 2;".format(i,x)

            if node[1] != "in":
                print >> decl, "clock x{0};".format(i)
                proc = Template("Node{0}".format(i))
                down = Location("down", initial=True)
                down.set_invariant("x{0} &lt;= {1}".format(i, self.delays[i][0]))
                up = Location("up")
                up.set_invariant("x{0} &lt;= {1}".format(i, self.delays[i][1]))

                node_ready = self.node_ready(node)
                node_outputs_true = self.node_output_true(node)

                if bound == None or inode != 0:
                    proc.add_transition(Transition(down, up, guard="x{0} &lt;= {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[0], up="out{0} := 1".format(i)))
                else:
                    print >> decl, "clock t;"
                    bg = " &amp;&amp; t &lt;= {0}".format(bound)
                    proc.add_transition(Transition(down, up, guard="{1} &lt;= x{0} &amp;&amp; x{0} &lt;= {2}".format(i, self.delays[i][0], self.delays[i][1]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[0] + bg, up="out{0} := 1".format(i)))
                proc.add_transition(Transition(down, up, guard="{1} &lt;= x{0} &amp;&amp; x{0} &lt;= {2} ".format(i, self.delays[i][0], self.delays[i][1]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[1], up="out{0} := 0".format(i)))
#                    proc.add_transition(Transition(down, up, guard="x{0} &lt;= {1}".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[0] + bg, up="out{0} :
#                proc.add_transition(Transition(down, up, guard="x{0} &lt;= {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[1], up="out{0} := 0".format(i)))
                proc.add_transition(Transition(down, down, guard="x{0} == {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[1], up="x{0} := 0".format(i)))

                proc.add_transition(Transition(up, down, guard="x{0} &lt;={1}".format(i, self.delays[i][1]), up="x{0}:=0".format(i)))

                if inode == 0:
                    proc.add_transition(Transition(up,Location("err"), guard="out{0}==1".format(i)))
                nta.add_template(proc)

        input_nodes = filter(lambda n: n[1] == "in", graph)
        proc = Template("Inputs")
        prev_loc = Location("input_init", initial=True, committed=True)
        for node in input_nodes:
            loc = Location("In{0}".format(node[0]), committed=True)
            proc.add_transition(Transition(prev_loc, loc, up="out{0} := 1".format(node[0])))
            proc.add_transition(Transition(prev_loc, loc, up="out{0} := 0".format(node[0])))
            prev_loc = loc
        proc.add_transition(Transition(prev_loc, Location("end")))

        nta.add_template(proc)
        nta.set_declaration(decl.getvalue())
        nta.set_system("system " +  ", ".join(map(lambda x: x.name, nta.templates)) + ";")
        nta.dump()



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
        with open("{0}a{1}.xml".format(out_dir,i),"w") as f:
            sys.stdout = f
        # tawriter.test();
        # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
        # tawriter.dump_model(args.clocked_latches, args.bound)
            tawriter.dump_cyclic_graph(args.bound)
    for i,gr in enumerate(graph_sat):
        if gr == None:
            continue
        tawriter = TAWRITER(gr, args.time, args.numeric, 3000)
        with open("{0}b{1}.xml".format(out_dir, i),"w") as f:
            sys.stdout = f
        # tawriter.test();
        # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
        # tawriter.dump_model(args.clocked_latches, args.bound)
            tawriter.dump_cyclic_graph(args.bound)

if __name__ == "__main__":
    main()
    #dump_graph(graph1)
