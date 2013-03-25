#include <Python.h>

#include <sstream>
using namespace std;

#include <Viewer/EventSelectionScript.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>

EventSelectionScript::EventSelectionScript()
{
  stringstream pythonScriptPath;
  pythonScriptPath << getenv( "VIEWERROOT" ) << "/scripts/eventselect";
  PyObject* pSysPath = PySys_GetObject( "path" );
  PyObject* pPath = PyString_FromString( pythonScriptPath.str().c_str() );
  PyList_Append( pSysPath, pPath );
  //Py_DECREF( pSysPath );
  Py_DECREF( pPath );
  fpScript = NULL;
  fpSelectFunction = NULL;
}

EventSelectionScript::~EventSelectionScript()
{
  UnLoad();
}

void
EventSelectionScript::UnLoad()
{
  Py_XDECREF( fpScript ); // Delete old script if exists
  Py_XDECREF( fpSelectFunction );
}

void
EventSelectionScript::Load( const string& scriptName )
{
  if( scriptName != fCurrentScript )
    {
      UnLoad();
      // Load new script
      PyObject* pScriptName = PyString_FromString( scriptName.c_str() );
      fpScript = PyImport_Import( pScriptName ); // Load script
      Py_DECREF( pScriptName );
      fpSelectFunction = PyObject_GetAttrString( fpScript, "select" );
      if( !fpSelectFunction || !PyCallable_Check( fpSelectFunction ) )
        throw;
    }
  else
    {
      fpScript = PyImport_ReloadModule( fpScript ); // ReLoad script
      Py_DECREF( fpSelectFunction );
      fpSelectFunction = PyObject_GetAttrString( fpScript, "select" );
      if( !fpSelectFunction || !PyCallable_Check( fpSelectFunction ) )
        throw;
    }
  fCurrentScript = scriptName;
}

bool
EventSelectionScript::ProcessEvent( const RIDS::Event& event )
{
  return true;
}
