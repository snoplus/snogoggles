#include <Python.h>

#include <sstream>
using namespace std;

#include <Viewer/PMTSelectionScript.hh>
using namespace Viewer;

const int kNumChannels = 10000;

PMTSelectionScript::PMTSelectionScript()
{
  Py_InitializeEx(0); // Initialise without signal handlers
  fpScript = NULL;
}

PMTSelectionScript::~PMTSelectionScript()
{
  UnLoad();
  Py_Finalize();
}

void
PMTSelectionScript::UnLoad()
{
  Py_XDECREF( fpScript ); // Delete old script if exists
  Py_XDECREF( fpSelectFunction );
  Py_XDECREF( fpData ); // Delete old data if exists
}

void
PMTSelectionScript::Load( const string& scriptName )
{
  UnLoad();
  // Load new script
  stringstream pythonScriptPath;
  pythonScriptPath << getenv( "VIEWERROOT" ) << "/scripts/pmtselect";
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

  fpData = PyList_New( kNumChannels );
  ResetData();
}

void
PMTSelectionScript::Process()
{
  ResetData();
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpSelectFunction, fpData, NULL );
  //Py_DECREF( pResult );
}

vector<bool>
PMTSelectionScript::GetSelectionData() const
{
  vector<bool> lcnData;
  for( int lcn = 0; lcn < kNumChannels; lcn++ )
    {
      if( PyList_GetItem( fpData, lcn ) == Py_True )
        lcnData.push_back( true );
      else
        lcnData.push_back( false );
    }
  return lcnData;
}

void
PMTSelectionScript::ResetData()
{
  // Now fill the list with these empty values
  for( int iEntry = 0; iEntry < kNumChannels; iEntry++ )
    {
      PyList_SetItem( fpData, iEntry, Py_False ); // This steals the reference
    }
}

