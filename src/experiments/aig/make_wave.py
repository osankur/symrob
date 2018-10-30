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

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(4,8)]
n1 = (1, "th", 3, [inps[i] for i in range(0,4)])
n2 = (2, "th", 2, [n1, inps[0], inps[1], inps[2]])
n3 = (3, "or", [n1, n2])
n0 = (0, "and", [n3, inps[0]])
# the first one is the output gate.
graph1 = [n0,n1,n2,n3] + inps


inps = [(i, "in") for i in range(1,9)]
n1 = (9, "th", 4, [inps[i] for i in range(0,4)])
n2 = (10, "th", 4, [n1, inps[0], inps[1], inps[2], inps[3], inps[4]])
n3 = (11, "th", 3, [n1, n2, inps[4], inps[5],inps[6]])
n4 = (12, "th", 4, [n1, n3, inps[3], inps[4],inps[5]])
n5 = (13, "or", [n3, n4])
n6 = (14, "and", [n5, n2])
n0 = (0, "and", [n6, inps[0]])
# the first one is the output gate.
graph2 = [n0] + inps + [n1,n2,n3,n4,n5,n6]

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


    def node_ready(self, i):
        graph = self.graph
        if graph[i][1] == "and" or graph[i][1] == "or":
            g = "b{0}_0 &lt; 2 &amp;&amp; b{0}_1 &lt; 2".format(i)
            gn = "(!(b{0}_0 != 2) &amp;&amp; !(b{0}_1 != 2)) == 0".format(i)
            return (g, gn)
        elif graph[i][1] == "th":
            g =  " &amp;&amp; ".join(map(lambda x: "b{0}_{1} &lt; 2".format(i,x), range(len(graph[i][3]))))
            gn =  " &amp;&amp; ".join(map(lambda x: "(b{0}_{1} != 2".format(i,x), range(len(graph[i][3])))) + ")"*len(graph[i][3]) + " == 0"
            return (g,gn)
        elif graph[i][1] == "in":
            return ("true", "false")
        else:
            raise Exception("unknown gate")

    def node_output_true(self, i):
        graph = self.graph
        if graph[i][1] == "and":
            g = "b{0}_0 == 1 &amp;&amp; b{0}_1 == 1".format(i)
            gn = "(b{0}_0 == 1 &amp;&amp; b{0}_1 == 1) == 0".format(i)
            #gn = "(b{0}_0 == 0 || b{0}_1 == 0)".format(i)
            return (g, gn)
        elif graph[i][1] == "or":
            #g =  "(b{0}_0 == 1 || b{0}_1 == 1)".format(i)
            g =  "(b{0}_0 == 0 &amp;&amp; b{0}_1 == 0) == 0".format(i)
            gn =  "b{0}_0 == 0 &amp;&amp; b{0}_1 == 0".format(i)
            return (g, gn)
        elif graph[i][1] == "th":
            g =  "+".join(map(lambda x: "(b{0}_{1}".format(i,x), range(len(graph[i][3]))))+ ")"*len(graph[i][3]) + " &gt;= {0}".format(graph[i][2]) 
            gn =  "+".join(map(lambda x: "(b{0}_{1}".format(i,x), range(len(graph[i][3]))))+ ")"*len(graph[i][3]) + " &lt; {0}".format(graph[i][2])
            return (g, gn)
        if graph[i][1] == "in":
            return ("true", "false")
        else:
            raise Exception("unknown gate")

    def dump_graph(self):
        print >> sys.stderr, self.delays
        graph = self.graph
        # outputs[x] is the set of node ids y such that some input of y comes from node of id x
        outputs = map(lambda x: [], graph)
        for node in graph:
            outputs[node[0]] = set([])

        for node in graph:
            inps = []
            if node[1] == "th":
                inps = node[3]
            elif node[1] == "and" or node[1] == "or":
                inps = node[2]
            elif node[1] == "in":
                inps = []
            else:
                raise Exception("Unknown gate")
            for i in inps:
                outputs[i[0]].add(node[0])
        print >> sys.stderr, "outputs: ", list(enumerate(outputs))

        nta = NTA()
        decl = StringIO.StringIO()
        print >> decl, "clock t;"
        # for each node i, with outputs out
        for (i, out) in enumerate(outputs):
            ins = []
            #if graph[i][1] == "in":
            #    print >> decl, "int[0,1] i{0};".format(i)
            if graph[i][1] == "and" or graph[i][1] == "or":
                print >> decl, "int[0,2] b{0}_0 = 2;".format(i)
                print >> decl, "int[0,2] b{0}_1 = 2;".format(i)
                print >> decl, "int[0,1] out{0};".format(i)
                ins = graph[i][2]
            elif graph[i][1] == "th":
                print >> decl, "int[0,1] out{0};".format(i)
                for x in range(len(graph[i][3])):
                    print >> decl, "int[0,2] b{0}_{1} = 2;".format(i,x)
                ins = graph[i][3]
            for j in out:
                # channel names: ch_X_Y_bZ means node of id(x) sends bit Z to node of id(y)
                print >> sys.stderr, "chan {0} -> {1}".format(i, j)
                print >> decl, "chan ch_{0}_{1}_b0;".format(i,j)
                print >> decl, "chan ch_{0}_{1}_b1;".format(i,j)
            print >> decl, "clock x{0};".format(i)

            if graph[i][1] != "in":
                proc = Template("Node{0}".format(graph[i][0]))

                wait = Location("wait", initial=True)
                check = Location("check", committed=True)
                processing = Location("processing")
                processing.set_invariant("x{0} &lt;= {1}".format(i, self.delays[i][1]))

                up = Location("up", committed=True)
                done = Location("done")

                node_ready = self.node_ready(i)
                node_outputs_true = self.node_output_true(i)

                proc.add_transition(Transition(check, wait, node_ready[1]))
                proc.add_transition(Transition(check, processing, node_ready[0] + " &amp;&amp; " + node_outputs_true[0],
                                               up="out{0} := 1, x{0} := 0".format(i)))
                proc.add_transition(Transition(check, processing, node_ready[0] + " &amp;&amp; " + node_outputs_true[1],
                                               up="out{0} := 0, x{0} := 0".format(i)))
                proc.add_transition(Transition(processing, up, guard="{0} &lt;= x{1} &amp;&amp; x{1} &lt;= {2}".format(self.delays[i][0], i, self.delays[i][1])))

                # ins is the list of nodes that are the inputs of the i-th node
                for i_in_node, in_node in enumerate(ins):
                    print >> sys.stderr, "for node: {2}: input{0} by node({1})".format(i_in_node, in_node[0], graph[i][0])
                    #print >> sys.stderr, "b{0}_{1} := X".format(i, i_in_node)
                    #print >> sys.stderr, "\ti_in_node: {0}, in_node[0]: {1}".format(i_in_node, in_node[0])
                    proc.add_transition(Transition(wait, check, sync="ch_{0}_{1}_b0?".format(in_node[0], graph[i][0]),
                                                   up="b{0}_{1} := 0".format(i, i_in_node)))
                    proc.add_transition(Transition(wait, check, sync="ch_{0}_{1}_b1?".format(in_node[0], graph[i][0]),
                                                   up="b{0}_{1} := 1".format(i, i_in_node)))

                    proc.add_transition(Transition(processing, processing, sync="ch_{0}_{1}_b0?".format(in_node[0], graph[i][0])))
                    proc.add_transition(Transition(processing, processing, sync="ch_{0}_{1}_b1?".format(in_node[0], graph[i][0])))
                    proc.add_transition(Transition(done,done,sync="ch_{0}_{1}_b0?".format(in_node[0],graph[i][0])))
                    proc.add_transition(Transition(done,done,sync="ch_{0}_{1}_b1?".format(in_node[0],graph[i][0])))
                prev_loc = up
                for (oi, o) in enumerate(outputs[i]):
                    loc = Location("up{0}_{1}".format(i,o), committed=True)
                    proc.add_transition(Transition(prev_loc, loc, guard="out{0} == 1".format(i), sync="ch_{0}_{1}_b1!".format(graph[i][0], o)))
                    proc.add_transition(Transition(prev_loc, loc, guard="out{0} == 0".format(i), sync="ch_{0}_{1}_b0!".format(graph[i][0], o)))
                    prev_loc = loc
                proc.add_transition(Transition(prev_loc, done))

                # Add spec for the first gate
                if i == 0:
                    assert(graph[i][0] != "in")
                    err = Location("err")
                    proc.add_transition(Transition(wait, err, guard="t &gt;= {0}".format(self.bound)))
                    proc.add_transition(Transition(processing, err, guard="t &gt;= {0}".format(self.bound)))
                nta.add_template(proc)


        #inputs
        print >> sys.stderr, map(lambda n: n[0], graph)
        locs = map(lambda n: (n[0], Location("In{0}".format(n[0]), committed=True)), filter(lambda n: n[1] == "in", graph))
        locs = [(-1,Location("input_init", initial=True, committed=True))] + locs
        print >> sys.stderr, locs
        proc = Template("Inputs")
        prev_loc0 = locs[0][1]
        prev_loc1 = locs[0][1]

        count = 1
        print >> sys.stderr, "** locs: {0} < {1}".format(count, len(proc.locs))
        for (i, inloc) in locs[1:]:
            #proc.add_transition(Transition(prev_loc, inloc))
            #print >> sys.stderr, outputs[i]
            print >> sys.stderr, "Node id: ", i
            for (oi, o) in enumerate(outputs[i]):
                print >> sys.stderr, "\t output id:", oi
                loc0 = Location("up{0}_{1}_b0".format(i, o), committed=True)
                loc1 = Location("up{0}_{1}_b1".format(i, o), committed=True)
                count = count + 2
                proc.add_transition(Transition(prev_loc0, loc0, sync="ch_{0}_{1}_b0!".format(graph[i][0], o)))
                proc.add_transition(Transition(prev_loc1, loc1, sync="ch_{0}_{1}_b1!".format(graph[i][0], o)))
                print >> sys.stderr, "** locs: {0} < {1}".format(count, len(proc.locs))
                prev_loc0 = loc0
                prev_loc1 = loc1
            proc.add_transition(Transition(prev_loc0, inloc))
            proc.add_transition(Transition(prev_loc1, inloc))

            prev_loc0 = inloc
            prev_loc1 = inloc
        proc.add_transition(Transition(prev_loc0, Location("done")))
        nta.add_template(proc)

        print >> sys.stderr, "total: {0} < {1}".format(count, len(proc.locs))

        #print decl.getvalue()
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
    tawriter = TAWRITER(graph2, args.time, 3000)
    # tawriter.test();
    # print >> sys.stderr, "Given #clocked_latches: ", args.clocked_latches
    # tawriter.dump_model(args.clocked_latches, args.bound)
    tawriter.dump_graph()

if __name__ == "__main__":
    main()
    #dump_graph(graph1)
