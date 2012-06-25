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
    env.ParseConfig( os.path.join(ROOTSYS, 'root-config') + " --cflags --ldflags --libs ")
    env.Append( CPPPATH = [ os.environ["ROOTSYS"] + "/include"])
    env.Append( LIBS = 'PyROOT' )
  
# Appends SFML and GLEW
def sfml(env):
    env.Append( CPPPATH = [ os.environ["SFMLROOT"] + "/include", os.environ["GLEWROOT"] + "/include" ] )
    env.Append( LIBPATH = [ os.environ["SFMLROOT"] + "/lib", os.environ["GLEWROOT"] + "/lib" ] )
    env.Append( LIBS = [ 'sfml-graphics', 'sfml-window', 'sfml-system', 'GLEW' ] )
    # Need to put an "If APPLE" wrapper around this
    if "Darwin" in os.environ["G4SYSTEM"]:
        env.Append(LINKFLAGS=['-framework', 'OpenGL'])
# Appends RAT
def rat(env):
    env.Append( CPPPATH = [ os.environ["RATROOT"] + "/include" ] )
    env.Append( LIBPATH = [ os.environ["RATROOT"] + "/lib" ] )
    env.Append( LIBS = [ 'rat_' + os.environ["G4SYSTEM"] ] )
    Curl(env)

# Appends Curl and Bzip (for RAT)
def Curl(env):
    env.Append( LIBS = [ "bz2", "curl" ] )
    if "BZIPROOT" in os.environ:
        env['CPPPATH'].append( os.environ['BZIPROOT'] + "/include" )
        env['LIBPATH'].append( os.environ['BZIPROOT'] + "/lib" )
    env.ParseConfig( "curl-config --cflags --libs" )

def glut(env):
    env.Append( LIBPATH="/usr/X11/lib" )
    # Need to put an "If APPLE" wrapper around this
    if "Darwin" in os.environ["G4SYSTEM"]:
        env.Append( LINKFLAGS=['-framework', 'glut'])
    env.Append( LIBS = ["glut", "GLU", "GL"])

# Appends Pthread
def PThread(env):
    env.Append( LIBS = [ "pthread" ] )

# Append Avalanche and zmq
def Avalanche(env):
    avalancheLibPath = os.path.join(os.environ['AVALANCHEROOT'], "lib/cpp")
    env.Append( CPPPATH = [ avalancheLibPath, os.environ['ZEROMQROOT'] + "/include" ] )
    env.Append( LIBPATH = [ avalancheLibPath, os.environ['ZEROMQROOT'] + "/lib" ] )
    env.Append( LIBS = [ "avalanche", "zmq" ] )

# Append Python libraries
def Python(env):
    ldflags = env.backtick( "python-config --includes --libs --ldflags").split() # Split on space, diff flags
    # Put all options after -u in LINKFLAGS, may not have a -u part though
    try: 
        idx = ldflags.index('-u') 
        env.Append( LINKFLAGS=ldflags[idx:] ) 
        del ldflags[idx:] # Remove the -u part
    except ValueError: 
        idx = -1 
    env.MergeFlags( ' '.join( ldflags ) ) 
    
# Adds all packages
def addpackages(env):
    Python(env)
    xercesc(env)
    geant4(env)
    sfml(env)
    rat(env)
    root(env)
    PThread(env)
    Avalanche(env)
    glut(env)    

