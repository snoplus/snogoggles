#!/usr/bin/env python
# Author P G Jones - 18/10/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

def event(in_data, out_data):
    """ This function counts the number of hits per channel."""
    for lcn in range(0, len(in_data["cal"])):
        if in_data["uncal"][lcn][0] > 0.0: 
            out_data[lcn][0] += 1.0
        if in_data["uncal"][lcn][1] > 0.0: 
            out_data[lcn][1] += in_data["uncal"][lcn][1]
        if out_data[lcn][0] > 500.0:
            out_data[lcn][0] = 500.0
        if out_data[lcn][1] > 50000.0:
            out_data[lcn][1] = 50000.0
    return None

def reset(out_data):
    """ This function clears all the data."""
    for lcn in range(0, len(out_data[0])):
        out_data[lcn][0] = 0.0
        out_data[lcn][1] = 0.0
        out_data[lcn][2] = 0.0
        out_data[lcn][3] = 0.0
    return None

def get_labels():
    """ Reutrn the data labels."""
    return ("Occupancy", "Sum Charge", "N/a", "N/a")
