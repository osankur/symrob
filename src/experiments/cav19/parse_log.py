import sys
import os
import os.path
import re
import argparse


def parse(filename, mc):
    with open(filename, 'r') as filehandle:
        content = filehandle.read()
    cl = re.split("-BEGIN-", content)
    for case in cl:
        if case == "":
            continue
        result = None
        time = None
        clock_preds = None
        cegar_its = None
        error = False
        peak = None
        filename = None
        if mc == "symrob":
            if "Result: true" in case:
                result = True
            elif "Result: false" in case:
                result = False
            times = re.search("/ (\d+\.\d+) sec", case)
            if times <> None:
                time = times.group(1)
            if "timeout or error" in case:
                error = True
            m = re.search("CEGAR iterations: (\d+) w/ (\d+) clock predicates", case)
            if m <> None:
                cegar_its = m.group(1)
                clock_preds = m.group(2)
            m = re.search("Node peak: (\d+)", case)
            if m <> None:
                peak = m.group(1)
            m = re.search("=+ ([^=]+) =+", case)
            if m <> None:
                filename = os.path.basename(m.group(1))
            if not error:
                print "{0};\t\t{1};\t\t{2};\t\t{3};\t\t;{4};\t\t{5};\t\t{6}".format(filename, time, result, error, clock_preds, cegar_its, peak)
        if mc == "uppaal":
            if "Property is satisfied." in case:
                result = True
            elif "Property is NOT satisfied." in case:
                result = False
            times = re.search("/ (\d+\.\d+) sec", case)
            if times <> None:
                time = times.group(1)
            if "timeout or error" in case:
                error = True
            m = re.search("=+ ([^=]+) =+", case)
            if m <> None:
                filename = os.path.basename(m.group(1))
            if not error:
                print "{0};\t\t{1};\t\t{2};\t\t{3};".format(filename, time, result, error)
        if mc == "pat":
            times = re.search("/ (\d+\.\d+) sec", case)
            if times <> None:
                time = times.group(1)
            if "timeout or error" in case:
                error = True
            m = re.search("=+ ([^=]+) =+", case)
            if m <> None:
                filename = os.path.basename(m.group(1))
            if not error:
                print "{0};\t\t{1};\t\t{2};\t\t{3};".format(filename, time, result, error)
        if mc == "tchecker":
            if "TCHECKER_OUTCOME false" in case:
                result = True
            elif "TCHECKER_OUTCOME true" in case:
                result = False
            times = re.search("/ (\d+\.\d+) sec", case)
            if times <> None:
                time = times.group(1)
            m = re.search("=+ ([^=]+) =+", case)
            if m <> None:
                filename = os.path.basename(m.group(1))
            if "timeout or error" in case:
                error = True
            if not error:
                print "{0};\t\t{1};\t\t{2}".format(filename, time, result)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generation or Execution of AIG Tests")
    parser.add_argument("file", metavar="file", type=str)
    parser.add_argument("-p", "--program", dest="program", type=str, required=True,
                        help=("symrob, uppaal, or PAT"))
#    parser.add_argument("-f", "--factor", dest="factor", type=str,required=True)
    args = parser.parse_args()
    mc = args.program
    filename = args.file
    parse(filename, mc)
