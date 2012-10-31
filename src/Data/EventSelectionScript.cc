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
  PyObject* fpInput = PyString_FromString( fInputString.c_str() );
  bool result = false;
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpSelectFunction, pDataDict, fpInput, NULL );
  if( pResult == Py_True )
    result = true;
  Py_XDECREF( pResult );
  Py_DECREF( pDataDict );
  Py_DECREF( fpInput );
  return result;
}
