#include <Python.h>

#include <sstream>
#include <iostream>
using namespace std;

#include <Viewer/AnalysisScript.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>

const int kNumChannels = 10000;

AnalysisScript::AnalysisScript()
{
  stringstream pythonScriptPath;
  pythonScriptPath << getenv( "VIEWERROOT" ) << "/scripts/analysis";
  PyObject* pSysPath = PySys_GetObject( "path" );
  PyObject* pPath = PyString_FromString( pythonScriptPath.str().c_str() );
  PyList_Append( pSysPath, pPath );
  //Py_DECREF( pSysPath );
  Py_DECREF( pPath );
  fpScript = NULL;
  fpEventFunction = NULL;
  fpResetFunction = NULL;
  fpData = NULL;
}

AnalysisScript::~AnalysisScript()
{
  UnLoad();
}

void
AnalysisScript::UnLoad()
{
  Py_XDECREF( fpScript ); // Delete old script if exists
  Py_XDECREF( fpEventFunction );
  Py_XDECREF( fpResetFunction );
  Py_XDECREF( fpData ); // Delete old data if exists
}

void
AnalysisScript::Load( const string& scriptName )
{
  if( scriptName != fCurrentScript )
    {
      UnLoad();
      // Load new script
      PyObject* pScriptName = PyString_FromString( scriptName.c_str() );
      fpScript = PyImport_Import( pScriptName ); // Load script
      Py_DECREF( pScriptName );
    }
  else
    {
      fpScript = PyImport_ReloadModule( fpScript );// ReLoad script
      Py_DECREF( fpEventFunction );
      Py_DECREF( fpResetFunction );
    }
  fpEventFunction = PyObject_GetAttrString( fpScript, "event" );
  if( !fpEventFunction || !PyCallable_Check( fpEventFunction ) )
    throw;
  fpResetFunction = PyObject_GetAttrString( fpScript, "reset" );
  if( !fpResetFunction || !PyCallable_Check( fpResetFunction ) )
    throw;
  PyObject* pLabelsFunction = PyObject_GetAttrString( fpScript, "get_labels" );
  if( !pLabelsFunction || !PyCallable_Check( pLabelsFunction ) )
    throw;
  PyObject* pResult = PyObject_CallFunctionObjArgs( pLabelsFunction, NULL );
  fDataLabels.clear();
  for( int label = 0; label < 4; label++ )
    {
      fDataLabels.push_back( string( PyString_AsString( PyTuple_GetItem( pResult, label ) ) ) );
    }
  Py_DECREF( pResult );

  Py_DECREF( pLabelsFunction );
  fCurrentScript = scriptName;
  //fpData = NewEmptyPyList();
}

void
AnalysisScript::Reset()
{
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpEventFunction, fpData, NULL );
  Py_DECREF( pResult );
}

void
AnalysisScript::ProcessEvent( const RIDS::Event& event )
{

}
