"""
Stuff
"""
from subprocess import Popen, PIPE

data = [
    ("test5.xml", "test5a.q", "syntax", False),
    ("test5.xml", "test5b.q", "syntax", True),
    ("test5.xml", "test5c.q", "syntax", False),
    ("test5.xml", "test5d.q", "syntax", True),
    ("test5.xml", "test5d.q", "syntax", True),
    ("test6.xml", "test6a.q", "bounded", True),
    ("test1.xml", "test1_1.q", "syntax", False),
    ("test1.xml", "test1_2.q", "empty", False),
    ("test1.xml", "test1_3.q", "empty", True),
    ("test1.xml", "test1_4.q", "empty", True),
    ("test1.xml", "test1_5.q", "empty", False),
    ("test1.xml", "test1_6.q", "syntax", True),
    ("test2.xml", "test2.q", "complete", False),
    ("test2.xml", "test2_2.q", "complete", False)
    ]
ret_code = 0
for case in data:
    tafile = case[0]
    qfile = case[1]
    result = case[3]
    output = Popen(['../../symrob', '-c', tafile, qfile], stdout=PIPE)
    answer = output.stdout.read()
    if "Reachable: true" in answer:
        if result:
            print tafile, " ", qfile, "\t [OK]"
        else:
            print tafile, " ", qfile, " !! FALSE NEGATIVE !!"
            ret_code = -1
    elif "Reachable: false" in answer:
        if not result:
            print tafile, " ", qfile, "\t [OK]"
        else:
            print tafile, " ", qfile, " [!! FALSE POSITIVE !!]"
            ret_code = -1
    else:
        print "Unknown answer to pair: ", tafile, " ", qfile
