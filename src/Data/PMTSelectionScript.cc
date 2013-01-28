#include <Python.h>

#include <RAT/DS/PMTProperties.hh>

#include <sstream>
using namespace std;

#include <Viewer/PMTSelectionScript.hh>
using namespace Viewer;

PMTSelectionScript::PMTSelectionScript()
{
  stringstream pythonScriptPath;
  pythonScriptPath << getenv( "VIEWERROOT" ) << "/scripts/pmtselect";
  PyObject* pSysPath = PySys_GetObject( "path" );
  PyObject* pPath = PyString_FromString( pythonScriptPath.str().c_str() );
  PyList_Append( pSysPath, pPath );
  //Py_DECREF( pSysPath );
  Py_DECREF( pPath );
  fpScript = NULL;
  fpSelectFunction = NULL;
  fpData = NULL;
  fpPMTData = NULL;
}

PMTSelectionScript::~PMTSelectionScript()
{
  Py_DECREF( fpPMTData );
  UnLoad();
}

void
PMTSelectionScript::Initialise( RAT::DS::PMTProperties& pmtProp )
{
  fChannels = pmtProp.GetPMTCount();
  fpPMTData = PyList_New( fChannels );
  for( int iEntry = 0; iEntry < fChannels; iEntry++ )
    {
      PyObject* pData = PyList_New( 2 );
      PyList_SetItem( pData, 0, PyLong_FromLong( pmtProp.GetType( iEntry ) ) );
      //PyList_SetItem( pData, 1, PyLong_FromLong( pmtProp.GetSNOMANNumber( iEntry ) ) );
      PyList_SetItem( fpPMTData, iEntry, pData ); // This steals the reference
    }
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
  fpData = PyList_New( fChannels );
  ResetData();
}

void
PMTSelectionScript::Process()
{
  ResetData();
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpSelectFunction, fpPMTData, fpData, NULL );
  //Py_DECREF( pResult );
}

vector<bool>
PMTSelectionScript::GetSelectionData() const
{
  vector<bool> lcnData;
  for( int lcn = 0; lcn < fChannels; lcn++ )
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
  for( int iEntry = 0; iEntry < fChannels; iEntry++ )
    {
      PyList_SetItem( fpData, iEntry, Py_True ); // This steals the reference
    }
}

