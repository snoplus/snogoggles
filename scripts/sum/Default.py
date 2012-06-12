#!/usr/bin/env python
# Author P G Jones - 22/04/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

def Event( inti, outi ):
    for lcn in range( 0, len( inti["cal"] ) ):
        if inti["cal"][lcn][0] > 0.0:
            outi[lcn][0] += 1.0
        if inti["uncal"][lcn][0] > 0.0: # Charge
            outi[lcn][1] += 1.0
    return None
