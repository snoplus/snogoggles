#-*-python-*-
# Main build script for SNOGoggles.

#### Add new source module names here ####

directories = Split("""Graphics Viewer Frames Frames/Frames2d Frames/Frames3d Frames/Frames3d/Camera Frames/Frames3d/Hits Frames/Frames3d/Tracks Frames/Frames3d/Geo Frames/Frames3d/Fitter Util Configuration GUI GUI/GUIs Thread""")

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

# Find what architure we are using
ROOTSYS = os.path.join(os.environ["ROOTSYS"], 'bin')
ROOTARCH = os.popen(os.path.join(ROOTSYS, 'root-config') + ' --arch').read().strip()

# Adds all packages used by the viewer
addpackages(env)

# Temp always in debug
env.Append(CXXFLAGS=["-g"])
env.Append(LINKFLAGS=["-g"])

# Add a link to the include directory of the viewer
env.Append( CPPPATH = [ os.environ["VIEWERROOT"] + "/include" ] )

# Creates SNOGoggles Library
# Can be used by RAT to create a RAT processor version of SNOGoggles
env.StaticLibrary( os.environ["VIEWERROOT"] + "/lib/snogoggles", viewer_obj)

# Creates binary file
env.Program(target = 'bin/snogoggles', source = [ viewer_obj, "SNOGoggles.cc" ])
