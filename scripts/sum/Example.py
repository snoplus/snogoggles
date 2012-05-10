#!/usr/bin/env python
# Author P G Jones - 22/04/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

def Hello( inti, outi ):
    print len( inti["cal"] )
    print len( inti["cal"][0] )
    print inti["cal"][0][0]
    print "Hi"
    for lcn in range( 0, len( inti["cal"] ) ):
        if inti["cal"][lcn][0] > 0.0:
            outi[lcn][0] += 1.0
    return [3.0, 2.0, 1.0]
