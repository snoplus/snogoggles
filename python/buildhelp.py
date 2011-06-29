# Helper file used by SCons to build the Viewer.

import os
import glob
import shutil
import filecmp

# Global variable with the include directory.
inc_dir = "include/Viewer"

# Checks whether the include directory exists.
# If not, it makes the include directory.
def check_include():
	if  os.path.isdir( inc_dir ) == False:
		os.makedirs( inc_dir )

# Clears all files from the include directory.
# Right now, this function is not used.
def clear_include():
	files = glob.glob( inc_dir + "/*" )
	for f in files:
		os.remove(f)	

# Copies a file from old_file to new_file.
# Prints a message to the user informing them of the copy.
def copy_file( old_file, new_file ):
	print "Copying (\"" + old_file + "\") to (\"" + new_file + "\")..."
	shutil.copy(old_file, new_file)

# Checks whether the exact file exists in the include directory.
# If not, copies it to the include directory.
def copy_to_include(src_header, src_dir):
	inc_header = inc_dir + src_header.replace( src_dir, "" )
	if os.path.isfile( inc_header ):
		if filecmp.cmp( src_header, inc_header ) == False:
			copy_file( src_header, inc_header )
	else:
		copy_file( src_header, inc_header )
	

# Adds every source file to the object list for compilation.
def build_list(srcpath, build_dir):
	return [os.path.join(build_dir, os.path.basename(item)) for item in glob.glob(srcpath)]

# Deals with all of the files in the source module.
# If the file contains source code, adds it to the build.
# If the file is a header, copies it to the include directory.
def src_module(env, module_name):
	build_dir = os.path.join( "build", module_name )
	src_dir = os.path.join('src', module_name)
	env.VariantDir(build_dir, src_dir, duplicate=0)
	
	headers = glob.glob(src_dir + '/*.hh')
	
	for h in headers:
		copy_to_include(h, src_dir)
	
	return env.Object(build_list(os.path.join(src_dir,'*.cc'), build_dir))
