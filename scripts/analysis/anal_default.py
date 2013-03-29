#!/usr/bin/env python
# Author P G Jones - 18/10/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

def event(in_data, out_data):
    """ This function counts the number of hits per channel."""
    if "MC" in in_data: # Has mc Source
        for channel in range(0, len(in_data["MC"]["PE"])):
            if in_data["MC"]["PE"][channel] > 0.0:
                out_data["MC Sum"][channel] = out_data["MC Sum"][channel] + in_data["MC"]["PE"][channel]
    if "UnCal" in in_data: # Has UnCal Source
        for channel in range(0, len(in_data["UnCal"]["TAC"])):
            if in_data["UnCal"]["TAC"] > 0.0:
                if in_data["UnCal"]["TAC"][channel] > 0.0:
                    out_data["UnCal Sum"][channel] = out_data["UnCal Sum"][channel] + 1.0
    if "Cal" in in_data: # Has Cal Source
        for channel in range(0, len(in_data["Cal"]["TAC"])):
            if in_data["Cal"]["TAC"] > 0.0:
                if in_data["Cal"]["TAC"][channel] > 0.0:
                    out_data["Cal Sum"][channel] = out_data["Cal Sum"][channel] + 1.0
    return None

def reset(out_data):
    """ This function clears all the data."""
    print "Reset"
    return None

def get_types():
    """ Reutrn the data types."""
    return ("MC Sum", "UnCal Sum", "Cal Sum")
