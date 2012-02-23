#-*-python-*-
# Main build script for SNOGoggles.

#### Add new source module names here ####
directories = Split("""Graphics Graphics/Colour Viewer Frames Frames/Frames2d Frames/Frames2d/Utility Frames/Frames2d/Histograms Frames/Frames2d/Projections Util Geo Configuration GUI GUI/GUIs Thread Data""")
#directories = Split("""Graphics Graphics/Colour Viewer Frames Frames/Frames2d Frames/Frames2d/Utility Frames/Frames2d/Histograms Frames/Frames2d/Projections Frames/Frames3d 3DModules 3DModules/Camera  3DModules/Fitter 3DModules/Geo 3DModules/Hits 3DModules/Tracks Util Geo Configuration GUI GUI/GUIs Thread Data""")

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
