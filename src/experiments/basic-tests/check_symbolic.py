"""
Stuff
"""
from subprocess import Popen, PIPE

data = [
    ("test1.xml", "test1_1.q", "syntax", True),
    ("test1.xml", "test1_2.q", "empty", True),
    ("test1.xml", "test1_3.q", "empty", False),
    ("test1.xml", "test1_4.q", "empty", False),
    ("test1.xml", "test1_5.q", "empty", True),
    ("test1.xml", "test1_6.q", "syntax", False),
    ("test2.xml", "test2.q", "complete", True),
    ("test2.xml", "test2_2.q", "complete", True)
    ]
ret_code = 0
for case in data:
    tafile = case[0]
    qfile = case[1]
    result = case[3]
    output = Popen(['../../symrob', '-s', tafile, qfile], stdout=PIPE)
    answer = output.stdout.read()
    if "[INF] VERDICT: NOT REACHABLE" in answer:
        if result:
            print tafile, " ", qfile, "\t [OK]"
        else:
            print tafile, " ", qfile, " !! FALSE NEGATIVE !!"
            ret_code = -1
    elif "[INF] VERDICT: REACHABLE" in answer:
        if not result:
            print tafile, " ", qfile, "\t [OK]"
        else:
            print tafile, " ", qfile, " [!! FALSE POSITIVE !!]"
            ret_code = -1
    else:
        print "Unknown answer to pair: ", tafile, " ", qfile
