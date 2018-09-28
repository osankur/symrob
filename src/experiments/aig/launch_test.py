#!/usr/bin/python3.5
from __future__ import print_function
from subprocess import STDOUT, check_output, TimeoutExpired
from subprocess import *
import sys
import os
import re
import errno
import sys
import dataset
import argparse

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def parse_symrob(fname, output):
    times = re.findall("\d+\.\d+", output)
    verdict = None
    if "Result: true" in output:
        verdict = True
    elif "Result: false" in output:
        verdict=False
    eprint(output)
    print(fname, times[0],verdict)

def parse_uppaal(fname, output):
    times = re.findall("\d+\.\d+", output)
    verdict = None
    if "Property is satisfied." in output:
        verdict = True
    elif "Property is NOT satisfied." in output:
        verdict = False
    eprint(output)
    print(fname, times[0],verdict)


def test_mono(factor, prog, timeout):
    tests_dir = "monoprocess{0}".format(factor)
    ext = ".xml"
    if prog == 2:
        ext= ".ta"
    tests = sorted([tests_dir + '/' + f
                    for f in os.listdir(tests_dir) if f.endswith(ext)])
    for fname in tests:
        eprint("Testing: " + fname)
        if prog == 0:
            cmd = ["time", "symrob", "-c", fname, "mono.q", "--silent"]
            parse = parse_symrob
        elif prog == 1:
            cmd = ["time", "verifytga", fname, "mono.q"]
            parse = parse_uppaal
        elif prog == 2:
            raise Exception("Not implemented yet")
        try:
            output = check_output(cmd, timeout=timeout, stderr=STDOUT)
            parse(fname, output.decode())
        except TimeoutExpired:
            print(fname, " timeout")
            eprint(fname, " timeout")
        except CalledProcessError as e:
            print(fname, " error: ", e.returncode)
            eprint(fname, " error:\n", e.output.decode())


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generation or Execution of AIG Tests")
    parser.add_argument("-t", "--test", action="store_true")
    parser.add_argument("-b", "--benchtype", dest="benchtype", type=int,
                        help=("0 for mono, 1 for multi"))
    parser.add_argument("-p", "--program", dest="program", type=int, required=True,
                        help=("0 for symrob, 1 for Uppaal, 2 for PAT"))
    parser.add_argument("-f", "--factor", dest="factor", type=str,required=True)
    parser.add_argument("--timeout", dest="timeout", type=int, default=216000)
    args = parser.parse_args()
    if args.test:
        for i in [1,10,100]:
            gen_mono(i);
            gen_multiprocess(i);
    else:
        if args.benchtype == 0:
            test_mono(args.factor, args.program, args.timeout)
        elif args.benchtype == 1:
            test_multi(args.factor, args.program, args.timout)
        else:
            raise Exception("Unknown bench type")
