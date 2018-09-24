
# This should be static to the Location class
Loc_id = 0

class NTA:
    def __init__(self):
        self.templates = []
        self.decl = ""
        self.inst = ""
        self.query = ""
        self.system= ""

    def add_template(self, t):
        self.templates.append(t)
    def set_declaration(self, decl):
        self.decl = decl

    def dump(self):
        print "<TA><Declaration>", self.decl
        for temp in self.templates:
            temp.dump()
        print  "</Declaration><Processes/></TA>"
class Template:
    def __init__(self, name):
        self.name = name
        self.decl = ""
        self.locs = []
        self.trans = []

    def add_location(self, loc):
        if not loc in self.locs:
            self.locs.append(loc)
    def add_locations(self, locs):
        iter(lambda l: self.add_location(l), locs)

    def add_transition(self, tr):
        if not tr in self.trans:
            self.trans.append(tr)
            self.add_location(tr.src)
            self.add_location(tr.tgt)

    def dump(self):
        #print "<Process Name=\"{0}\" Param=\"\" Zoom=\"1\" StateCounter=\"{1}\">".format(self.name,len(self.locs)+1)
        print "TimedAutomaton {0}".format(self.name)
        print "{"
        print self.decl
        for loc in self.locs:
            loc.dump(self.trans)
        print "}"

class Location:
    def __init__(self, name="", urgent=False, committed=False,initial=False, error=False):
        global Loc_id
        self.name = name
        self.id = "loc" + str(Loc_id)
        self.urgent = urgent
        self.committed = committed
        self.initial = initial
        self.invariant = ""
        self.error = error
        Loc_id = Loc_id + 1

    def set_invariant(self, invar):
        self.invariant = invar

    def dump(self, trans):
        #print "<State Name=\"{0}\" Init=\"{1}\" Invariant=\"{2}\" IsUrgent=\"{3}\" IsCommitted=\"{4}\" IsError=\"{5}\"></State>".format(self.name, self.initial, self.invariant, self.urgent, self.committed, self.error)
        print "\tstate {0}\t".format(self.name)
        if self.urgent:
            print "\turgent;"
        if self.committed:
            print "\tcommitted;"
        if self.invariant:
            print "\tinv: {0};".format(self.invariant)
        for tr in trans:
            if tr.src == self:
                tr.dump()
        print "\tendstate\n"

class Transition:
    def __init__(self, src, tgt, guard="", disc_guard="", sync="", reset="", disc_up=""):
        self.src = src
        self.tgt = tgt
        self.guard = guard
        self.sync = sync
        self.reset = reset
        self.disc_guard = disc_guard
        self.disc_up = disc_up
    def dump(self):
        print "\ttrans:",
        if self.guard <> "":
            print "[[{0}]]".format(self.guard),
        if self.disc_guard <> "":
            print "[{0}]".format(self.disc_guard),
        if self.sync <> "":
            print self.sync,
        else:
            print "tau",
        if self.disc_up <> "":
            print "{", self.disc_up, "}",
        if self.reset <> "":
            print "&lt;{0}&gt;".format(self.reset),
        print "-&gt;{0};".format(self.tgt.name)
