from subprocess import Popen, PIPE,call
import os
data_dir = "data/"
verbose = False
dataset_mono = [("amba3b5y.aag", "time", 4, 290,  True),
           ("amba3b5y.aag", "time", 4, 200,  True),
           ("amba3b5y.aag", "time", 4, 300,  False),
           ("amba3b5y.aag", "time", 5, 290,  True),
           ("amba3b5y.aag", "time", 5, 300,  False),
           ("genbuf5f5n.aag", "time", 5, 290,  True),
           ("genbuf5f5n.aag", "time", 5, 300,  False),
           ("cnt5y.aag", "time", 4, 200, True),
           ("cnt5y.aag", "time", 4, 300, False),
           ("bs16y.aag", "time", 4, 200, False),
           ("bs16y.aag", "time", 4, 100, True),
           ("bs16y.aag", "time", 4, 150, False),
           ("moving_obstacle_8x8_1glitches.aag", "time", 4, 150, True),
           ("moving_obstacle_8x8_1glitches.aag", "time", 4, 300, False),
           ("amba4c7y.aag","time",4,300, False),
           ("amba4c7y.aag","time",4,200, True),
           ("factory_assembly_3x3_1_1errors.aag", "time", 4, 300, False),
           ("factory_assembly_3x3_1_1errors.aag", "time", 4, 200, True),
           ("factory_assembly_3x3_1_1errors.aag", "time", 5, 300, False),
           ("factory_assembly_3x3_1_1errors.aag", "time", 6, 300, True),
           ("factory_assembly_3x3_1_1errors.aag", "time", 6, 400, True),
           ("factory_assembly_3x3_1_1errors.aag", "time", 6, 500, False),
           ("genbuf2b3unrealy.aag", "time", 4, 300, False),
           ("genbuf2b3unrealy.aag", "time", 5, 300, False),
           ("genbuf2b3unrealy.aag", "time", 5, 250, True),
          ]
def gen_mono():
    for case in dataset_mono:
        input = case[0]
        time = case[1]
        nbL = case[2]
        bound = case[3]
        res = case[4]
        target_file = "monoprocess/" + os.path.basename(input) + "_{0}L_{1}.xml".format(nbL,bound)
        if verbose:
            print "python make_mono.py", data_dir+input, time, nbL, bound
        output = Popen(["python", "make_mono.py", data_dir+input, time, str(nbL), str(bound)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

        target_file_pat = "monoprocess/" + os.path.basename(input) + "_{0}L_{1}.ta".format(nbL,bound)
        if verbose:
            print "python make_pat_mono.py", data_dir+input, time, nbL, bound
        output = Popen(["python", "make_pat_mono.py", data_dir+input, time, str(nbL), str(bound)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file_pat,"w")
        f.write(answer)
        f.close()


dataset_multi = [("amba3b5y.aag", "cnt3y.aag", "cnt3y.aag", 0, True),
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

def gen_multiprocess():
    for (i,case) in enumerate(dataset_multi):
        specs = map(lambda x: data_dir + x, case[0:3])
        mode = case[3]
        target_file = "multiprocess/model" + str(i) + ".ta"
        if verbose:
            print "python make_pat_multi.py", specs[0], specs[1], specs[2], mode
        output = Popen(["python", "make_pat_multi.py",specs[0], specs[1], specs[2], str(mode)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

        target_file = "multiprocess/model" + str(i) + ".xml"
        if verbose:
            print "python make_multi.py", specs[0], specs[1], specs[2], mode
        output = Popen(["python", "make_multi.py",specs[0], specs[1], specs[2], str(mode)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()
        print "Model" + str(i), specs

if __name__ == "__main__":
    gen_mono();
    gen_multiprocess();
