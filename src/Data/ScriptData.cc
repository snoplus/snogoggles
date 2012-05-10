#include <Python.h>

#include <iostream>
#include <sstream>
using namespace std;

#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/ScriptData.hh>
using namespace Viewer;

const int kNumChannels = 10000;

void
ScriptData::Initialise()
{
  Py_Initialize();
  stringstream pythonScriptPath;
  pythonScriptPath << getenv( "VIEWERROOT" ) << "/scripts/sum";
  PySys_SetPath( const_cast<char*>( pythonScriptPath.str().c_str() ) ); // Annoying python api
  PyObject* pScriptName = PyString_FromString( "Example" );
  fpScript = PyImport_Import( pScriptName ); // Load script
  Py_DECREF( pScriptName );
  fpFunction = PyObject_GetAttrString( fpScript, "Hello" );
  if( !fpFunction || !PyCallable_Check( fpFunction ) )
    throw;

  fpData = NewEmptyPyList();
}

void
ScriptData::ProcessEvent( const RIDS::Event& event )
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
  
  PyObject* pResult = PyObject_CallFunctionObjArgs( fpFunction, pDataDict, fpData, NULL );
  Py_DECREF( pResult );
  Py_DECREF( pDataDict );
}

vector<RIDS::PMTHit>
ScriptData::GetHitData() const
{
  vector<RIDS::PMTHit> hitData;
  for( int lcn = 0; lcn < kNumChannels; lcn++ )
    {
      hitData.push_back( RIDS::PMTHit( PyList_GetItem( fpData, lcn ), lcn ) );
    }
  return hitData;
}

PyObject*
ScriptData::NewEmptyPyList()
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
ScriptData::FillList( const RIDS::Event& event,
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

