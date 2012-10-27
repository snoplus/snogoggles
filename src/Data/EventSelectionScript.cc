#include <Python.h>

#include <sstream>
using namespace std;

#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/EV.hh>
#include <Viewer/EventSelectionScript.hh>
using namespace Viewer;

EventSelectionScript::EventSelectionScript()
{
  Py_InitializeEx(0); // Initialise without signal handlers
  fpScript = NULL;
}

EventSelectionScript::~EventSelectionScript()
{
  UnLoad();
  Py_Finalize();
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
  UnLoad();
  // Load new script
  stringstream pythonScriptPath;
  pythonScriptPath << getenv( "VIEWERROOT" ) << "/scripts/eventselect";
  PyObject* pSysPath = PySys_GetObject( "path" );
  PyObject* pPath = PyString_FromString( pythonScriptPath.str().c_str() );
  PyList_Append( pSysPath, pPath );
  //Py_DECREF( pSysPath );
  Py_DECREF( pPath );
  PyObject* pScriptName = PyString_FromString( scriptName.c_str() );
  fpScript = PyImport_Import( pScriptName ); // Load script
  Py_DECREF( pScriptName );
  fpSelectFunction = PyObject_GetAttrString( fpScript, "select" );
  if( !fpSelectFunction || !PyCallable_Check( fpSelectFunction ) )
    throw;
}

bool
EventSelectionScript::ProcessEvent( const RIDS::Event& event )
{
  /// Build data to send to the script
  PyObject* pDataDict = PyDict_New();
  PyObject* pTrigger;
  PyObject* pNhit;
  if( event.ExistEV() )
    {
      pTrigger = PyInt_FromLong( event.GetEV().GetTriggerWord() );
      pNhit = PyInt_FromLong( event.GetEV().GetUnCalNHits() );
    }
  else
    {
      pTrigger = PyInt_FromLong( 0 );
      pNhit = PyInt_FromLong( 0 );
    }
  PyDict_SetItemString( pDataDict, "trigger", pTrigger );
  Py_DECREF( pTrigger );
  PyDict_SetItemString( pDataDict, "nhit", pNhit );
  Py_DECREF( pNhit );

  /// Call the script, check the result and return true/false
  bool result = false;
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpSelectFunction, pDataDict, NULL );
  if( pResult == Py_True )
    result = true;
  Py_XDECREF( pResult );
  Py_DECREF( pDataDict );
  return result;
}
