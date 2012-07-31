#!/usr/bin/env python
# Author P G Jones - 07/06/2012 <p.g.jones@qmul.ac.uk> : First revision
# This fills the data with random numbers
import random

def Event( inti, outi ):
    for lcn in range( 0, len( inti["cal"] ) ):
        outi[lcn][0] = random.random() * 500.0
        outi[lcn][1] = lcn / 512.0 * 10.0#random.random() * 4000.0
        outi[lcn][2] = lcn / 32.0 #random.random() * 4000.0
        outi[lcn][3] = 0.0#random.random() * 1000.0
    return None
