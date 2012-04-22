#!/usr/bin/env python
# Author P G Jones - 22/04/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

def Hello( interestamond ):
    print interestamond
    print resultArray
    print "Hi"

def SumEvent( event, result ):
    """ Sum this event to the resultVector. This just sums up the number of PMT hits in the TAC channel."""
    if event.GetEVCount() == 0:
        return
    for ipmt in range( 0, event.GetEV(0).GetPMTCalCount() ):
        print "Summing", ipmt
        pmtCal = event.GetEV(0).GetPMTCal( ipmt )
        resultPMT = result.At( pmtCal.GetID() )
        resultPMT.SetTime( resultPMT.GetTime() + 1.0 )
    return

def Clear( result ):
    """ Clear the result, which should be a TObjArray."""
    for ipmt in range( 0, result.GetEntriesFast() ):
        print "Clearing", ipmt
        pmtCal = result.At( ipmt )
        pmtCal.SetTime( 0.0 )
        pmtCal.SetsQHS( 0.0 )
        pmtCal.SetsQHL( 0.0 )
        pmtCal.SetsQLX( 0.0 )
    return
