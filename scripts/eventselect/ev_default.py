#!/usr/bin/env python
# Author P G Jones - 18/10/2012 <p.g.jones@qmul.ac.uk> : First revision
# This is the example summing script 

def select(data):
    """ """
    if data['nhit'] < 1:
        return False
    if data['trigger'] != 0:
        return True
    else:
        return False
