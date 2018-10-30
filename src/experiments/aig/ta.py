
# This should be static to the Location class
Loc_id = 0

class NTA:
    def __init__(self):
        self.templates = []
        self.decl = ""
        self.inst = ""
        self.query = ""
        self.system= ""

    def set_instantiation(self, inst):
        self.inst = inst
    def set_query(self, query):
        self.query = query
    def set_system(self, system):
        self.system= system
    def add_template(self, t):
        self.templates.append(t)
    def set_declaration(self, decl):
        self.decl = decl

    def dump(self):
        print """<?xml version="1.0" encoding="utf-8"?><!DOCTYPE nta PUBLIC '-//Uppaal Team//DTD Flat System 1.1//EN' 'http://www.it.uu.se/research/group/darts/uppaal/flat-1_1.dtd'>"""
        print "<nta><declaration>", self.decl, "</declaration>"
        for temp in self.templates:
            temp.dump()
        print "<instantiation>{0}</instantiation>".format(self.inst)
        print "<system>{0}</system>".format(self.system)
        if self.query:
            print "<queries><query><formula>", self.query, "</formula></query></queries>"
        print "</nta>"

class Template:
    def __init__(self, name):
        self.name = name
        self.decl = ""
        self.locs = []
        self.trans = []

    def set_declaration(self, decl):
        self.decl = decl

    def add_location(self, loc):
        if not loc in self.locs and loc.name in map(lambda x: x.name, self.locs):
            raise Exception("Location of name " + loc.name + " already present")
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
        print "<template><name>{0}</name>".format(self.name)
        if self.decl <> "":
            print "<declaration>{0}</declaration>".format(self.decl)
        for loc in self.locs:
            loc.dump()
        for loc in self.locs:
            if loc.initial:
                print "<init ref=\"{0}\"/>".format(loc.id)
        for tr in self.trans:
            tr.dump()
        print "</template>"

class Location:
    def __init__(self, name="", urgent=False, committed=False,initial=False):
        global Loc_id
        self.name = name
        self.id = "loc" + str(Loc_id)
        self.urgent = urgent
        self.committed = committed
        self.initial = initial
        self.invariant = None
        Loc_id = Loc_id + 1

    def set_invariant(self, invar):
        self.invariant = invar

    def dump(self):
        print "<location id=\"{0}\"><name>{1}</name>".format(self.id, self.name)
        if self.urgent:
            print "<urgent/>"
        if self.committed:
            print "<committed/>"
        if self.invariant:
            print "<label kind=\"invariant\">{0}</label>".format(self.invariant)
        print "</location>"

class Transition:
    def __init__(self, src, tgt, guard=None, sync=None, up=None):
        self.src = src
        self.tgt = tgt
        self.guard = guard
        self.sync = sync
        self.up = up
    def dump(self):
        print "<transition>\n<source ref=\"{0}\"/><target ref=\"{1}\"/>".format(self.src.id,self.tgt.id)
        if self.sync <> None:
            print "<label kind=\"synchronisation\">{0}</label>".format(self.sync)
        if self.up <> None:
            print "<label kind=\"assignment\">{0}</label>".format(self.up)
        if self.guard <> None:
            print "<label kind=\"guard\">{0}</label>".format(self.guard)
        print "</transition>"
