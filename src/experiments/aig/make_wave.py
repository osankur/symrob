import sys
import random
import argparse
import log
from ta import *
from itertools import chain
import StringIO
numeric_mode = False
# majority, and, or, 
# threshold(n,k)

graph = [None]*10

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(4,8)]
n1 = (1, "th", 3, [inps[i] for i in range(0,4)])
n2 = (2, "th", 2, [n1, inps[0], inps[1], inps[2]])
n3 = (3, "or", [n1, n2])
#n0 = (0, "and", [n3, inps[0]])
n0 = (0, "and", [inps[1], inps[0]])
# the first one is the output gate.
graph[0] = [n0,n1,n2,n3] + inps


inps = [(i, "in") for i in range(1,9)]
n1 = (9, "th", 4, [inps[i] for i in range(0,4)])
n2 = (10, "th", 4, [n1, inps[0], inps[1], inps[2], inps[3], inps[4]])
n3 = (11, "th", 3, [n1, n2, inps[4], inps[5],inps[6]])
n4 = (12, "th", 4, [n1, n3, inps[3], inps[4],inps[5]])
n5 = (13, "or", [n3, n4])
n6 = (14, "and", [n5, n2])
n0 = (0, "and", [n6, inps[0]])
# the first one is the output gate.
graph[1] = [n0] + inps + [n1,n2,n3,n4,n5,n6]

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(4,40)]
n1 = (1, "th", 10, [inps[i] for i in range(0,35)])
n2 = (2, "th", 10, [inps[i] for i in range(0,20)] + [n1])
n3 = (3, "or", [n1, n2])
n0 = (0, "and", [n3, inps[0]])
# the first one is the output gate.
graph[2] = [n0,n1,n2,n3] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(4,20)]
n1 = (1, "th", 10, [inps[i] for i in range(0,10)])
n2 = (2, "th", 10, [inps[i] for i in range(10,15)] + [n1])
n3 = (3, "or", [n1, n2])
n0 = (0, "and", [inps[1], inps[0]])
# the first one is the output gate.
graph[3] = [n0,n1,n2,n3] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(5,20)]
n1 = (1, "th", 10, [inps[i] for i in range(0,10)])
n2 = (2, "th", 10, [inps[i] for i in range(10,15)] + [n1])
n3 = (3, "or", [n1, n2])
n4 = (4, "not", n3)
n0 = (0, "and", [n3, n4])
# the first one is the output gate.
graph[4] = [n0,n1,n2,n3,n4] + inps



#outputs:  [(0, set([])), (1, set([0, 9, 10])), (2, set([9, 10])), (3, set([9, 10])), (4, set([9, 10, 12])), (5, set([10, 11, 12])), (6, set([11, 12])), (7, set([11])), (8, set([])), (9, set([10, 11, 12])), (10, set([11, 14])), (11, set([12, 13])), (12, set([13])), (13, set([14])), (14, set([0]))]


class TAWRITER:
    def __init__(self, graph, time, bound):
        self.factor=1
        self.delays = []
        self.graph = graph
        self._read_delays(time)
        self.bound = bound

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
            g = "out{0} &lt; 2 &amp;&amp; out{0} &lt; 2".format(inps[0][0], inps[1][0])
            gn = "(out{0} != 2 &amp;&amp; out{0} != 2) == 0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "th":
            inps = node[3]
            g =  " &amp;&amp; ".join(map(lambda x: "out{0} &lt; 2".format(x[0]), inps))
            gn =  " &amp;&amp; ".join(map(lambda x: "(out{0} != 2".format(x[0]), inps)) + ")"*len(inps) + " == 0"
            return (g,gn)
        elif node[1] == "in":
            return ("1==1", "0==1")
        elif node[1] == "not":
            return ("out{0}&lt;2".format(i), "out{0}&lt;2".format(i))
        else:
            raise Exception("unknown gate")

    def node_output_true(self, node):
        if node[1] == "and":
            inps = node[2]
            g = "out{0} == 1 &amp;&amp; out{0} == 1".format(inps[0][0], inps[1][0])
            gn = "(out{0} == 1 &amp;&amp; out{0} == 1)==0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "or":
            inps = node[2]
            g = "(out{0} == 0 &amp;&amp; out{0} == 0) == 0".format(inps[0][0], inps[1][0])
            gn = "out{0} == 0 &amp;&amp; out{0} == 0".format(inps[0][0], inps[1][0])
            return (g, gn)
        elif node[1] == "th":
            inps = node[3]
            g =  "+".join(map(lambda x: "(out{0}".format(x[0]), inps))+ ")" * len(inps) + " &gt;= {0}".format(node[2])
            gn =  "+".join(map(lambda x: "(out{0}".format(x[0]), inps))+ ")" * len(inps) + " &lt; {0}".format(node[2])
            return (g, gn)
        elif node[1] == "not":
            return ("(1-out{0})==1".format(i), "(1-out{0}) ==0".format(i))
        if node[1] == "in":
            return ("1==1", "0==1")
        else:
            raise Exception("unknown gate")

    def dump_cyclic_graph(self):
        print >> sys.stderr, self.delays
        graph = self.graph


        nta = NTA()
        decl = StringIO.StringIO()

        for inode,node in enumerate(graph):
            i = node[0]
            print >> decl, "int[0,2] out{0};".format(i)
            ins = []
            if node[1] == "and" or node[1] == "or":
                print >> decl, "int[0,2] b{0}_0 = 2;".format(i)
                print >> decl, "int[0,2] b{0}_1 = 2;".format(i)
            elif node[1] == "th":
                for x in range(len(graph[i][3])):
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

                proc.add_transition(Transition(down, up, guard="x{0} &lt;= {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[0], up="out{0} := 1".format(i)))
                proc.add_transition(Transition(down, up, guard="x{0} &lt;= {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[0]  + " &amp;&amp; " + node_outputs_true[1], up="out{0} := 0".format(i)))
                proc.add_transition(Transition(down, down, guard="x{0} == {1} ".format(i, self.delays[i][0]) + " &amp;&amp; " + node_ready[1], up="x{0} := 0".format(i)))

                proc.add_transition(Transition(up, down, guard="x{0} &lt;={1}".format(i, self.delays[i][1]), up="out{0} := 2, x{0}:=0".format(i)))

                if inode == 0:
                    proc.add_transition(Transition(up,Location("err"), guard="out{0}==1".format(i)))
                nta.add_template(proc)

        input_nodes = filter(lambda n: n[0] == "in", graph)
        proc = Template("Inputs")
        prev_loc = Location("input_init", initial=True, committed=True)
        for node in input_nodes:
            loc = Location("In{0}".format(node[0]), committed=True)
            proc.add_transition(Transition(prev_loc, loc, up="out{0} := 1".format(i)))
            proc.add_transition(Transition(prev_loc, loc, up="out{0} := 0".format(i)))
        proc.add_transition(Transition(prev_loc, Location("end")))

        nta.add_template(proc)
        nta.set_declaration(decl.getvalue())
        nta.set_system("system " +  ", ".join(map(lambda x: x.name, nta.templates)) + ";")
        nta.dump()



def main():
    global numeric_mode
    parser = argparse.ArgumentParser(description="AIG Format Based Synth")
    #parser.add_argument("ninputs", metavar="ninputs", type=int,
    #                    help="Number of input modules (at top level)")
    #parser.add_argument("clocked_latches", metavar="clocked", type=int,
    #                    help="number of clocked modules")
    parser.add_argument("time", metavar="time", type=str,
                        help="input file for time intervals")
    parser.add_argument("-v", "--verbose_level", dest="verbose_level",
                        default="", required=False,
                        help="Verbose level = (D)ebug, (W)arnings, " +
                             "(L)og messages, (B)DD dot dumps")
    parser.add_argument("-n", "--numeric", action="store_true",
                        help=("Encode Boolean functions with number operations"))
    args = parser.parse_args()
    log.parse_verbose_level(args.verbose_level)
    numeric_mode = args.numeric
    # realizability / synthesis
    for i,gr in enumerate(graph):
        if gr == None:
            continue
        tawriter = TAWRITER(gr, args.time, 3000)
        with open("/tmp/a{0}.xml".format(i),"w") as f:
            sys.stdout = f
        # tawriter.test();
        # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
        # tawriter.dump_model(args.clocked_latches, args.bound)
            tawriter.dump_cyclic_graph()

if __name__ == "__main__":
    main()
    #dump_graph(graph1)
