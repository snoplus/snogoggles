#!/usr/bin/env python
# Author P G Jones - 31/10/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the default event selection script

triggers = {"100L" : 0x01,
           "100M" : 0x02,
           "100H" : 0x04,
           "20" : 0x08,
           "20L" : 0x10,
           "ESUML" : 0x20,
           "ESUMH" : 0x40,
           "OWL" : 0x80,
           "OWLL" : 0x100,
           "OWLH" : 0x200,
           "PUL" : 0x400,
           "PRE" : 0x800,
           "PED" : 0x1000,
           "PONG" : 0x2000,
           "SYNC" : 0x4000,
           "EXT" : 0x8000 }

def select(data, input_):
    """ """
    if len(input_) == 0 or not ':' in input_: # By default return true
        print "Malformed input, try TRIGGER:NHIT"
        return True
    split_input = input_.split(":")
    trigger_cuts = []
    if input_[0] != ':':
        trigger_cuts = split_input[0].split(",")
    nhit_cut = None
    if input_[-1] != ':':
        nhit_cut = split_input[1]
    good_event = False
    if len(trigger_cuts) == 0:
        good_event = True
    for t_cut in trigger_cuts:
        if not t_cut in triggers.keys():
            print t_cut, " is an unknown trigger, script failure."
            return True
        if data['trigger'] & triggers[t_cut]: # Has this trigger
            good_event = True
    if nhit_cut and nhit_cut.isdigit() and data['nhit'] < int(nhit_cut):
        good_event = False
    return good_event
