from subprocess import Popen, PIPE,call
import os
import errno
import sys
from dataset import *
import make_wave
import make_pat_wave
import make_tchecker_wave

# FIXME Why am I using process calls to call python??


data_dir = "data/"
verbose = True

def mono_file_name(factor, filename, nbL, bound, ext):
    dirname = "monoprocess{0}/".format(factor)
    base = os.path.basename(filename)
    return dirname + base + "_{0}L_{1}".format(nbL,bound) + ext

def gen_mono(factor):
    dirname = "monoprocess{0}/".format(factor)
    if not os.path.exists(os.path.dirname(dirname)):
        try:
            os.makedirs(os.path.dirname(dirname))
        except OSError as exc: # Guard against race condition
            if exc.errno != errno.EEXIST:
                raise
    with open(dirname+"log", "w") as f:
        for line in dataset_mono:
            f.write(str(line))
            f.write("\n")
    for case in dataset_mono:
        input = case[0]
        time = case[1]
        nbL = case[2]
        bound = case[3]
        res = case[4]
        target_file = mono_file_name(factor, input, nbL, bound, ".xml")
        if verbose:
            print "python make_mono.py", data_dir+input, time, nbL, bound
        output = Popen(["python", "make_mono.py", data_dir+input, time, str(nbL), str(bound), "-f", str(factor)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

        target_file = mono_file_name(factor, input, nbL, bound, ".ta")
        if verbose:
            print "python make_pat_mono.py", data_dir+input, time, nbL, bound
        output = Popen(["python", "make_pat_mono.py", data_dir+input, time, str(nbL), str(bound), "-f", str(factor)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

        target_file = mono_file_name(factor, input, nbL, bound, ".cpp")
        output = Popen(["python", "make_tchecker_mono.py", data_dir+input, time, str(nbL), str(bound), "-f", str(factor)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

def multi_file_name(factor, i, ext):
    dirname = "multiprocess{0}/".format(factor)
    return dirname + str(i) + ext

def gen_multiprocess(factor):
    dirname = "multiprocess{0}/".format(factor)
    if not os.path.exists(os.path.dirname(dirname)):
        try:
            os.makedirs(os.path.dirname(dirname))
        except OSError as exc: # Guard against race condition
            if exc.errno != errno.EEXIST:
                raise
    with open(dirname+"log", "w") as f:
        for (i, line) in enumerate(dataset_multi):
            f.write("Model"+str(i) + " ")
            f.write(str(line))
            f.write("\n")
    for (i,case) in enumerate(dataset_multi):
        specs = map(lambda x: data_dir + x, case[0:3])
        mode = case[3]
        target_file = multi_file_name(factor, i, ".ta")
        if verbose:
            print "python make_pat_multi.py", specs[0], specs[1], specs[2], mode
        output = Popen(["python", "make_pat_multi.py",specs[0], specs[1], specs[2], str(mode), "-f", str(factor)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

        target_file = multi_file_name(factor, i, ".xml")
        if verbose:
            print "python make_multi.py", specs[0], specs[1], specs[2], mode
        output = Popen(["python", "make_multi.py",specs[0], specs[1], specs[2], str(mode), "-f", str(factor)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()


        target_file = multi_file_name(factor, i, ".cpp")
        if verbose:
            print "python make_tchecker_multi.py", specs[0], specs[1], specs[2], mode
        output = Popen(["python", "make_tchecker_multi.py",specs[0], specs[1], specs[2], str(mode), "-f", str(factor)], stdout=PIPE)
        answer = output.stdout.read()
        f = open(target_file,"w")
        f.write(answer)
        f.close()

        print "Model" + str(i), specs

def str_of_bool(b):
    if b == False:
        return "f"
    else:
        return "t"

def gen_wave():
    dirname = "wave/"
    if not os.path.exists(os.path.dirname(dirname)):
        try:
            os.makedirs(os.path.dirname(dirname))
        except OSError as exc: # Guard against race condition
            if exc.errno != errno.EEXIST:
                raise
    for (i,(g, b, res)) in enumerate(dataset_wave_unsat):
        with open("{0}/a{1}_{2}.xml".format(dirname,i,str_of_bool(res)),"w") as f:
            sys.stdout = f
            taw = make_wave.TAWRITER(g, "time", False, b)
            taw.dump_cyclic_graph(b)

    for (i,g,b,res) in (dataset_wave_sat):
#        print >> sys.stderr, (b,res), "yields", "{0}/b{1}_{2}_{3}.xml".format(dirname,i,b,str_of_bool(res))
        with open("{0}/b{1}_{2}_{3}.xml".format(dirname,i,b,str_of_bool(res)),"w") as f:
            sys.stdout = f
            taw = make_wave.TAWRITER(g, "time", False, b)
            taw.dump_cyclic_graph(b)

    for (i,(g, b, res)) in enumerate(dataset_wave_unsat):
        with open("{0}/a{1}_{2}.ta".format(dirname,i,str_of_bool(res)),"w") as f:
            sys.stdout = f
            taw = make_pat_wave.TAWRITER(g, "time", False, b)
            taw.dump_cyclic_graph(b)

    for (i,g, b, res) in (dataset_wave_sat):
#        print >> sys.stderr, (b,res), "yields", "{0}/b{1}_{2}_{3}.xml".format(dirname,i,b,str_of_bool(res))
        with open("{0}/b{1}_{2}_{3}.ta".format(dirname,i,b,str_of_bool(res)),"w") as f:
            sys.stdout = f
            taw = make_pat_wave.TAWRITER(g, "time", False, b)
            taw.dump_cyclic_graph(b)

    for (i,(g, b, res)) in enumerate(dataset_wave_unsat):
        with open("{0}/a{1}_{2}.cpp".format(dirname,i,str_of_bool(res)),"w") as f:
            sys.stdout = f
            taw = make_tchecker_wave.TAWRITER(g, "time", False, b)
            taw.dump_cyclic_graph(b)

    for (i,g, b, res) in (dataset_wave_sat):
#        print >> sys.stderr, (b,res), "yields", "{0}/b{1}_{2}_{3}.xml".format(dirname,i,b,str_of_bool(res))
        with open("{0}/b{1}_{2}_{3}.cpp".format(dirname,i,b,str_of_bool(res)),"w") as f:
            sys.stdout = f
            taw = make_tchecker_wave.TAWRITER(g, "time", False, b)
            taw.dump_cyclic_graph(b)


if __name__ == "__main__":
    for i in [10,100]:
    #    gen_mono(i);
        gen_multiprocess(i);
    gen_wave();
