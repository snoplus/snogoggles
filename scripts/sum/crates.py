#!/usr/bin/env python
# Author P G Jones - 18/10/2012 <p.g.jones@qmul.ac.uk> : First revision
# This displays data from even crates in TAC & QHS and odd crates in QHL & QLX
#  lcn  = 512*icrate + 32*icard + ichan;

def event(in_data, out_data):
    """ This function counts the number of hits per channel."""
    for lcn in range(0, len(in_data["uncal"])):
        crate = lcn / 512
        if crate % 2 == 0:
            out_data[lcn][0] = in_data["uncal"][0]
            out_data[lcn][1] = in_data["uncal"][1]
        else:
            out_data[lcn][2] = in_data["uncal"][2]
            out_data[lcn][3] = in_data["uncal"][3]
    return None

def reset(in_data, out_data):
    """ This function clears all the data."""
    for lcn in range(0, len(out_data[0])):
        out_data[lcn][0] = 0.0
        out_data[lcn][1] = 0.0
        out_data[lcn][2] = 0.0
        out_data[lcn][3] = 0.0
    return None
