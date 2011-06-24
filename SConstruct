#-*-python-*-
# Main build script for SNOGoggles.

#### Add new source module names here ####

directories = Split("""  """)

############### You should not need to edit below this line ############

import os
from buildhelp import src_module, check_include
from packages import addpackages

# Get build environment
env = Environment()

# Checks whether the include directory exists
check_include()

# src_module() returns list for each directory.
viewer_obj = []
for d in directories:
	viewer_obj += src_module(env, d)

# Adds all packages used by the viewer
addpackages(env)

# Add a link to the include directory of the viewer
env.Append( CPPPATH = [ os.environ["VIEWER_BASE_DIR"] + "/include" ] )

# Creates SNOGoggles Library
# Can be used by RAT to create a RAT processor version of SNOGoggles
env.StaticLibrary( os.environ["VIEWER_BASE_DIR"] + "/lib/snogoggles", viewer_obj)

# Creates binary file
env.Program(target = 'bin/snogoggles', source = viewer_obj)
