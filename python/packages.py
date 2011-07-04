import os

# Appends Xerces-C++
def xercesc(env):
	env.Append( CPPPATH = [ os.environ["XERCESCROOT"] + "/include" ] )
	env.Append( LIBPATH = [ os.environ["XERCESCROOT"] + "/lib" ] )
	env.Append( LIBS = ['xerces-c'] )

# Appends Geant4 and CLHEP
def geant4(env):
	env.Append( CPPPATH = [ os.environ["G4INCLUDE"], os.environ["CLHEP_INCLUDE_DIR"] ] )
	env.Append( LIBPATH = [ os.path.join( os.environ["G4LIB"], os.environ["G4SYSTEM"] ), os.environ["CLHEP_LIB_DIR"] ] )
	env.Append( LIBS = ['CLHEP'] )
	env.ParseConfig('%s/liblist -m %s < %s/libname.map'.replace('%s', os.path.join(os.environ["G4LIB"], os.environ["G4SYSTEM"])))

# Appends ROOT
def root(env):
	ROOTSYS = os.path.join(os.environ["ROOTSYS"], 'bin')
	env.ParseConfig( os.path.join(ROOTSYS, 'root-config') + " --cflags --ldflags --libs")

# Appends SFML and GLEW
def sfml(env):
	env.Append( CPPPATH = [ os.environ["SFMLROOT"] + "/include", os.environ["GLEWROOT"] + "/include" ] )
	env.Append( LIBPATH = [ os.environ["SFMLROOT"] + "/lib", os.environ["GLEWROOT"] + "/lib" ] )
	env.Append( LIBS = [ 'sfml-graphics', 'sfml-window', 'sfml-system', 'GLEW' ] )

# Appends RAT
def rat(env):
	env.Append( CPPPATH = [ os.environ["RATROOT"] + "/include" ] )
	env.Append( LIBPATH = [ os.environ["RATROOT"] + "/lib" ] )
	env.Append( LIBS = [ 'rat_' + os.environ["G4SYSTEM"] ] )
	Curl(env)

# Appends Curl and Bzip (for RAT)
def Curl(env):
	env.Append( LIBS = [ "bz2", "curl" ] )

# Appends Pthread
def PThread(env):
	env.Append( LIBS = [ "pthread" ] )

# Adds all packages
def addpackages(env):
	xercesc(env)
	geant4(env)
	root(env)
	sfml(env)
	rat(env)
	PThread(env)
	
