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


def has_triggers(data, trigger_cuts):
    """ Check if the event data has the triggers."""
    event_passes = False # Assume false unless trigger present
    for t_cut in trigger_cuts:
        if not t_cut in triggers.keys():
            print t_cut, " is an unknown trigger, script failure."        
            return True # Safe get out
        if data['trigger'] & triggers[t_cut]:
            event_passes = True
    return event_passes

def omit_triggers(data, trigger_cuts):
    """ Check if the vent data has not got the triggers."""
    event_passes = True # Assume true unless trigger present
    for t_cut in trigger_cuts:
        if not t_cut[1:] in triggers.keys():
            print t_cut, " is an unknown trigger, script failure."        
            return True # Safe get out
        if data['trigger'] & triggers[t_cut[1:]]:
            event_passes = False
    return event_passes

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
    # Check the nhit first
    if nhit_cut is not None:
        if data['nhit'] < int(nhit_cut):
            return False
    # Now check the triggers
    event_passes = False
    if len(trigger_cuts) != 0 and trigger_cuts[0][0] == '-': # Check for trigger absence
        event_passes = omit_triggers(data, trigger_cuts)
    elif len(trigger_cuts) != 0 and trigger_cuts[0][0] != '-': # Check for trigger inclusion
        event_passes = has_triggers(data, trigger_cuts)
    return event_passes
