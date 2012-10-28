#include <Python.h>

#include <sstream>
using namespace std;

#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/AnalysisScript.hh>
using namespace Viewer;

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
      fpEventFunction = PyObject_GetAttrString( fpScript, "event" );
      if( !fpEventFunction || !PyCallable_Check( fpEventFunction ) )
        throw;
      fpResetFunction = PyObject_GetAttrString( fpScript, "reset" );
      if( !fpResetFunction || !PyCallable_Check( fpResetFunction ) )
        throw;
    }
  else
    {
      fpScript = PyImport_ReloadModule( fpScript );// ReLoad script
      Py_DECREF( fpEventFunction );
      fpEventFunction = PyObject_GetAttrString( fpScript, "event" );
      if( !fpEventFunction || !PyCallable_Check( fpEventFunction ) )
        throw;
      Py_DECREF( fpResetFunction );
      fpResetFunction = PyObject_GetAttrString( fpScript, "reset" );
      if( !fpResetFunction || !PyCallable_Check( fpResetFunction ) )
        throw;
    }
  fCurrentScript = scriptName;
  fpData = NewEmptyPyList();
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
  // First produce the (4) python lists of data (MC, PMTTruth, PMTUnCal, PMTCal)
  PyObject* pMC = FillList( event, RIDS::eMC );
  PyObject* pTruth = FillList( event, RIDS::eTruth );
  PyObject* pUnCal = FillList( event, RIDS::eUnCal );
  PyObject* pCal = FillList( event, RIDS::eCal );
  // Now place them into an appropriate dictionary
  PyObject* pDataDict = PyDict_New();
  PyDict_SetItemString( pDataDict, "mc", pMC ); // This increments the reference
  Py_DECREF( pMC );
  PyDict_SetItemString( pDataDict, "truth", pTruth );
  Py_DECREF( pTruth );
  PyDict_SetItemString( pDataDict, "uncal", pUnCal );
  Py_DECREF( pUnCal );
  PyDict_SetItemString( pDataDict, "cal", pCal );
  Py_DECREF( pCal );
  
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpEventFunction, pDataDict, fpData, NULL );
  //Py_DECREF( pResult );
  Py_DECREF( pDataDict );
}

vector<RIDS::PMTHit>
AnalysisScript::GetHitData() const
{
  vector<RIDS::PMTHit> hitData;
  for( int lcn = 0; lcn < kNumChannels; lcn++ )
    {
      hitData.push_back( RIDS::PMTHit( PyList_GetItem( fpData, lcn ), lcn ) );
    }
  return hitData;
}

PyObject*
AnalysisScript::NewEmptyPyList()
{
  PyObject* pList = PyList_New( kNumChannels );
  RIDS::PMTHit nonHit( 0.0, 0.0, 0.0, 0.0 ); // Empty hit
  // Now fill the list with these empty values
  for( int iEntry = 0; iEntry < kNumChannels; iEntry++ )
    {
      PyObject* pEmptyHit = nonHit.NewPyList();
      PyList_SetItem( pList, iEntry, pEmptyHit ); // This steals the reference
    }
  return pList;
}

PyObject*
AnalysisScript::FillList( const RIDS::Event& event,
                      RIDS::EDataSource source )
{
  PyObject* pList = NewEmptyPyList();
  vector<RIDS::PMTHit> hits = event.GetHitData( source );
  for( vector<RIDS::PMTHit>::iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      PyObject* pHitData = iTer->NewPyList();
      PyList_SetItem( pList, iTer->GetLCN(), pHitData );
    }
  return pList;
}

