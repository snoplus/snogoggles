#!/usr/bin/env python
# Author P G Jones - 18/10/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

triggers = {"nhit100Lo" : 0x01,
           "nhit100Med" : 0x02, 
           "nhit100High" : 0x04,
           "nhit20" : 0x08, 
           "nhit20lb" : 0x10,
           "esumLo" : 0x20,
           "esumHi" : 0x40,
           "owl" : 0x80,
           "owlLG" : 0x100,
           "owlHG" : 0x200,
           "pulse" : 0x400,
           "prescale" : 0x800,
           "pedestal" : 0x1000,
           "pong" : 0x2000,
           "sync" : 0x4000,
           "ext" : 0x8000 }

def select(data):
    """ """
    #for trigger, value in triggers.iteritems():
    #    print trigger, bool(data['trigger'] & value)
    if data['trigger'] & triggers['nhit100Lo'] or \
            data['trigger'] & triggers['nhit100Med'] or \
            data['trigger'] & triggers['nhit100High']:
        return True
    else:
        return False
