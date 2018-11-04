dataset_mono = [("amba3b5y.aag", "time", 4, 290,  True),
                ("amba3b5y.aag", "time", 4, 200,  True),
                ("amba3b5y.aag", "time", 4, 300,  False),
                ("amba3b5y.aag", "time", 5, 290,  True),
                ("amba3b5y.aag", "time", 5, 300,  False),
                ("amba3b5y.aag", "time", 6, 290,  True),
                ("amba3b5y.aag", "time", 6, 300,  False),
                ("amba3b5y.aag", "time", 7, 290,  True),
                ("amba3b5y.aag", "time", 7, 300,  False),
                ("amba3b5y.aag", "time", 8, 300,  False),
                ("amba3b5y.aag", "time", 9, 300,  False),
                ("amba3b5y.aag", "time", 10, 300,  False),
                ("genbuf5f5n.aag", "time", 5, 290,  True),
                ("genbuf5f5n.aag", "time", 5, 300,  False),
                ("genbuf5f5n.aag", "time", 6, 290,  True),
                ("genbuf5f5n.aag", "time", 6, 300,  False),
                ("genbuf5f5n.aag", "time", 7, 290,  True),
                ("genbuf5f5n.aag", "time", 7, 300,  False),
                ("genbuf5f5n.aag", "time", 8, 300,  False),
                ("genbuf5f5n.aag", "time", 9, 300,  False),
                ("genbuf5f5n.aag", "time", 10, 300,  False),
                ("cnt5y.aag", "time", 4, 200, True),
                ("cnt5y.aag", "time", 4, 300, False),
                ("bs16y.aag", "time", 4, 200, False),
                ("bs16y.aag", "time", 4, 100, True),
                ("bs16y.aag", "time", 4, 150, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 4, 150, True),
                ("moving_obstacle_8x8_1glitches.aag", "time", 4, 300, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 5, 150, True),
                ("moving_obstacle_8x8_1glitches.aag", "time", 5, 300, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 6, 150, True),
                ("moving_obstacle_8x8_1glitches.aag", "time", 6, 300, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 7, 150, True),
                ("moving_obstacle_8x8_1glitches.aag", "time", 7, 300, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 8, 300, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 9, 300, False),
                ("moving_obstacle_8x8_1glitches.aag", "time", 10, 300, False),
                ("amba4c7y.aag","time",4,300, False),
                ("amba4c7y.aag","time",4,200, True),
                ("amba4c7y.aag","time",5,300, False),
                ("amba4c7y.aag","time",5,200, True),
                ("amba4c7y.aag","time",6,300, False),
                ("amba4c7y.aag","time",7,300, False),
                ("amba4c7y.aag","time",8,300, False),
                ("amba4c7y.aag","time",9,300, False),
                ("amba4c7y.aag","time",10,300, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 4, 300, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 4, 200, True),
                ("factory_assembly_3x3_1_1errors.aag", "time", 5, 300, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 6, 300, True),
                ("factory_assembly_3x3_1_1errors.aag", "time", 6, 400, True),
                ("factory_assembly_3x3_1_1errors.aag", "time", 6, 500, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 7, 500, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 8, 500, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 9, 500, False),
                ("factory_assembly_3x3_1_1errors.aag", "time", 10, 500, False),
                ("genbuf2b3unrealy.aag", "time", 4, 300, False),
                ("genbuf2b3unrealy.aag", "time", 5, 300, False),
                ("genbuf2b3unrealy.aag", "time", 5, 250, True),
                ("genbuf2b3unrealy.aag", "time", 6, 300, True),
                ("genbuf2b3unrealy.aag", "time", 7, 400, None),
                ("genbuf2b3unrealy.aag", "time", 8, 400, None),
                ("genbuf2b3unrealy.aag", "time", 9, 400, None),
                ("genbuf2b3unrealy.aag", "time", 10, 400, None),
]




dataset_multi = [
    ("amba3b5y.aag", "add2y.aag", "add2y.aag", 1, True),
    ("cnt4y.aag", "cnt3y.aag", "cnt3y.aag", 0, False),
    ("cnt4y.aag", "cnt3y.aag", "cnt3y.aag", 1, True),
    ("cnt4y.aag", "cnt4y.aag", "cnt3y.aag", 0, True),
    ("cnt4y.aag", "cnt4y.aag", "cnt3y.aag", 1, True),
    ("cnt4y.aag", "cnt4y.aag", "cnt4y.aag", 0, False),
    ("cnt4y.aag", "cnt4y.aag", "cnt4y.aag", 1, True),
    ("cnt5y.aag", "cnt4y.aag", "cnt3y.aag", 0, False),
    ("amba3b5y.aag", "cnt3y.aag", "cnt3y.aag", 1, True),
    ("cnt5y.aag", "cnt3y.aag", "cnt3y.aag", 0, False),
    ("cnt5y.aag", "cnt3y.aag", "cnt3y.aag", 1, True),
    ("cnt3y.aag", "cnt3y.aag", "cnt3y.aag", 0, False),
    ("cnt3y.aag", "cnt3y.aag", "cnt3y.aag", 1, True),
    ("amba3b5y.aag", "add2y.aag", "add2y.aag", 1, True),
    ("amba3b5y.aag", "add2y.aag", "add2y.aag", 0, None),
    ("amba3b5y.aag", "add2y.aag", "cnt3y.aag", 1, True),
    ("amba3b5y.aag", "add2y.aag", "cnt3y.aag", 0, None),
    ("bs8y.aag", "add2y.aag", "add2y.aag", 0, False),
    ("bs8y.aag", "add2y.aag", "add2y.aag", 1, True),
    ("bs8y.aag", "bs8y.aag", "add2y.aag", 0, False),
    ("bs8y.aag", "bs8y.aag", "bs8y.aag", 0, False),
]

# UNSAT benchmarks
graph = [None]*11
# id, type, nb of inputs, threshold, list of inputs

# Logically unsat

inps = [(i, "in") for i in range(6,10)]
n1 = (1, "th", 3, [inps[i] for i in range(0,4)])
n2 = (2, "th", 2, [n1, inps[0], inps[1], inps[2]])
n3 = (3, "or", [n1, n2])
#n0 = (0, "and", [n3, inps[0]])
n4 = (4, "not", n3)
n0 = (0, "and", [n3, n4])
# the first one is the output gate.
graph[0] = [n0,n1,n2,n3,n4] + inps


# *s *u
inps = [(i, "in") for i in range(6,10)]
n1 = (1, "th", 3, [inps[i] for i in range(0,4)])
n2 = (2, "th", 2, [n1, inps[0], inps[1], inps[2]])
n3 = (3, "or", [n1, n2])
#n0 = (0, "and", [n3, inps[0]])
n4 = (4, "and", [inps[1], n3])
n5 = (5, "not", inps[1])
n0 = (0, "and", [n5, n4])
graph[1] = [n0,n1,n2,n3,n4,n5] + inps

#
inps = [(i, "in") for i in range(6,10)]
n1 = (1, "or", [inps[0], inps[1]])
n2 = (2, "and", [n1, inps[2]])
n3 = (3, "th", 2, [n1,n2,inps[3]])
n4 = (4, "not", n3)
n0 = (0, "and", [n3, n4])
graph[2] = [n0,n1,n2,n3,n4] + inps

inps = [(i, "in") for i in range(1,9)]
n1 = (9, "th", 4, [inps[i] for i in range(0,4)])
n2 = (10, "th", 4, [n1, inps[0], inps[1], inps[2], inps[3], inps[4]])
n3 = (11, "th", 3, [n1, n2, inps[4], inps[5],inps[6]])
n4 = (12, "th", 4, [n1, n3, inps[3], inps[4],inps[5]])
n5 = (13, "or", [n3, n4])
n6 = (14, "and", [n5, n2])
n7 = (15, "not", n6)
n0 = (0, "and", [n6, n7])
# the first one is the output gate.
graph[3] = [n0] + inps + [n1,n2,n3,n4,n5,n6,n7]

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(5,40)]
n1 = (1, "th", 10, [inps[i] for i in range(0,35)])
n2 = (2, "th", 10, [inps[i] for i in range(0,20)] + [n1])
n3 = (3, "or", [n1, n2])
n4 = (4, "not", n2)
n0 = (0, "and", [n3,n4])
# the first one is the output gate.
gates = [n0,n1,n2,n3,n4]
graph[4] = gates + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,20)]
n1 = (1, "th", 9, [inps[i] for i in range(0,10)])
n2 = (2, "th", 4, [inps[i] for i in range(9,14)])
n3 = (3, "th", 5, [inps[i] for i in range(9,14)])
n4 = (4, "not", n3)
n5 = (5, "th", 3, [n1, n2, n4])
n0 = (0, "th", 3, [n5,inps[9],n3])
# the first one is the output gate.
graph[5] = [n0,n1,n2,n3,n4,n5] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(5,20)]
n1 = (1, "th", 10, [inps[i] for i in range(0,10)])
n2 = (2, "th", 10, [inps[i] for i in range(10,15)] + [n1])
n3 = (3, "or", [n1, n2])
n4 = (4, "not", n3)
n0 = (0, "and", [n3, n4])
# the first one is the output gate.
graph[6] = [n0,n1,n2,n3,n4] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,10)]
n1 = (1, "or", [inps[0], inps[1]])
n2 = (2, "and", [n1, inps[2]])
n3 = (3, "th", 2, [n1,n2,inps[3]])
n4 = (4, "th", 2, [n3, inps[0], inps[1], inps[2]])
n4 = (4, "not", n3)
n0 = (0, "and", [n3, n4])
# the first one is the output gate.
graph[7] = [n0,n1,n2,n3,n4] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(7,10)]
n1 = (1, "not", inps[0])
n2 = (2, "not", inps[1])
n3 = (3, "and", [inps[0], inps[2]])
n4 = (4, "or", [n3, n1])
n5 = (5, "and", [n3, n2])
n6 = (6, "th", 5, [n4,n5,inps[0], inps[1], inps[2]])
n0 = (0, "and", [n6, n5])
# the first one is the output gate.
graph[8] = [n0,n1,n2,n3,n4,n5,n6] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,20)]
n1 = (1, "th", 10, [inps[i] for i in range(0,10)])
n2 = (2, "th", 10, [inps[i] for i in range(10,14)] + [n1])
n3 = (3, "or", [n1, n2])
n4 = (4, "not", n2)
n0 = (0, "and", [n3,n4])
# the first one is the output gate.
graph[9] = [n0,n1,n2,n3,n4] + inps

inps = [(i, "in") for i in range(1,9)]
n1 = (9, "th", 4, [inps[i] for i in range(0,4)])
n2 = (10, "th", 4, [n1, inps[0], inps[1], inps[2], inps[3], inps[4]])
n3 = (11, "th", 3, [n1, n2, inps[4], inps[5],inps[6]])
n4 = (12, "th", 4, [n1, n3, inps[3], inps[4],inps[5]])
n5 = (13, "or", [n3, n4])
n6 = (14, "and", [n5, n2])
n7 = (15, "not", n6)
n0 = (0, "and", [n6, n7])
# the first one is the output gate.
graph[10] = [n0] + inps + [n1,n2,n3,n4,n5,n6,n7]


# SAT benchmarks
graph_sat = [None] * 10

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(4,8)]
n1 = (1, "th", 3, [inps[i] for i in range(0,4)])
n2 = (2, "th", 2, [n1, inps[0], inps[1], inps[2]])
n3 = (3, "or", [n1, n2])
#n0 = (0, "and", [n3, inps[0]])
n0 = (0, "and", [inps[1], inps[0]])
# the first one is the output gate.
graph_sat[0] = [n0,n1,n2,n3] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,10)]
n1 = (1, "or", [inps[0], inps[1]])
n2 = (2, "and", [n1, inps[2]])
n3 = (3, "th", 2, [n1,n2,inps[3]])
n4 = (4, "th", 2, [n3, inps[0], inps[1], inps[2]])
n0 = (0, "and", [n3, n4])
# the first one is the output gate.
graph_sat[1] = [n0,n1,n2,n3,n4] + inps

inps = [(i, "in") for i in range(1,9)]
n1 = (9, "th", 4, [inps[i] for i in range(0,4)])
n2 = (10, "th", 4, [n1, inps[0], inps[1], inps[2], inps[3], inps[4]])
n3 = (11, "th", 3, [n1, n2, inps[4], inps[5],inps[6]])
n4 = (12, "th", 4, [n1, n3, inps[3], inps[4],inps[5]])
n5 = (13, "or", [n3, n4])
n6 = (14, "and", [n5, n2])
n7 = (15, "not", n6)
n0 = (0, "or", [n6, n7])
# the first one is the output gate.
graph_sat[2] = [n0] + inps + [n1,n2,n3,n4,n5,n6,n7]

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,20)]
n1 = (1, "th", 10, [inps[i] for i in range(0,10)])
n2 = (2, "th", 4, [inps[i] for i in range(10,14)])
n3 = (3, "or", [n1, n2])
n4 = (4, "not", n2)
n0 = (0, "and", [n3,n4])
# the first one is the output gate.
graph_sat[3] = [n0,n1,n2,n3,n4] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,20)]
n1 = (1, "th", 9, [inps[i] for i in range(0,10)])
n2 = (2, "th", 4, [inps[i] for i in range(9,14)])
n3 = (3, "th", 5, [inps[i] for i in range(9,14)])
n4 = (4, "not", n3)
n5 = (5, "th", 3, [n1, n2, n4])
n0 = (0, "and", [n5,inps[9]])
# the first one is the output gate.
graph_sat[4] = [n0,n1,n2,n3,n4,n5] + inps

# id, type, nb of inputs, threshold, list of inputs
inps = [(i, "in") for i in range(6,20)]
n1 = (1, "th", 9, [inps[i] for i in range(0,10)])
n2 = (2, "th", 4, [inps[i] for i in range(9,14)])
n3 = (3, "th", 5, [inps[i] for i in range(9,14)])
n4 = (4, "not", n3)
n5 = (5, "th", 3, [n1, n2, n4])
n0 = (0, "th", 3, [n5,inps[9],n2])
# the first one is the output gate.
graph_sat[5] = [n0,n1,n2,n3,n4,n5] + inps

dataset_wave_unsat = map(lambda g: (g, 1000, False), graph)
dataset_wave_sat = [(graph_sat[0], 50, True),
                    (graph_sat[0], 150, False),
                    (graph_sat[1], 50, False),
                    (graph_sat[1], 150, True),
                    (graph_sat[2], 50, False), # 2m30 - 6 ref
                    (graph_sat[2], 150, True), # 2m30 - 10 ref
                    (graph_sat[3], 150, False), # 45s - 21 ref
                    (graph_sat[3], 300, True), # 45s - 14 ref
                    (graph_sat[4], 300, False), # 10s
                    (graph_sat[5], 300, False), # 11s
]
