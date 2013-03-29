#include <Python.h>

#include <sstream>
#include <iostream>
using namespace std;

#include <Viewer/AnalysisScript.hh>
#include <Viewer/DataSelector.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/ChannelList.hh>

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
  stringstream scriptPath;
  scriptPath << "anal_" << scriptName;
  fCurrentScript = scriptPath.str();
  UnLoad();
  // Load new script
  PyObject* pScriptName = PyString_FromString( fCurrentScript.c_str() );
  fpScript = PyImport_Import( pScriptName ); // Load script
  Py_DECREF( pScriptName );
  fpEventFunction = PyObject_GetAttrString( fpScript, "event" );
  if( !fpEventFunction || !PyCallable_Check( fpEventFunction ) )
    throw;
  fpResetFunction = PyObject_GetAttrString( fpScript, "reset" );
  if( !fpResetFunction || !PyCallable_Check( fpResetFunction ) )
    throw;
  PyObject* pLabelsFunction = PyObject_GetAttrString( fpScript, "get_types" );
  if( !pLabelsFunction || !PyCallable_Check( pLabelsFunction ) )
    throw;
  PyObject* pResult = PyObject_CallFunctionObjArgs( pLabelsFunction, NULL );
  fTypes.clear();
  for( size_t iType = 0; iType < PyTuple_Size( pResult ); iType++ )
    {
      fTypes.push_back( string( PyString_AsString( PyTuple_GetItem( pResult, iType ) ) ) );
    }
  Py_DECREF( pResult );
  Py_DECREF( pLabelsFunction );
  // Reset the data
  Reset();
}

void
AnalysisScript::Reset()
{
  const RIDS::ChannelList& channelList = DataSelector::GetInstance().GetChannelList();

  Py_XDECREF( fpData );
  // Create the python data structure
  fpData = PyDict_New();
  // Add a list of channels for each type the script declares
  for( vector<string>::const_iterator iTer = fTypes.begin(); iTer != fTypes.end(); iTer++ )
    {
      PyObject* pList = PyList_New( channelList.GetChannelCount() );
      // Fill with empty doubles...
      for( size_t iChannel = 0; iChannel < channelList.GetChannelCount(); iChannel++ )
        PyList_SetItem( pList, iChannel, PyFloat_FromDouble( 0.0 ) );
      PyDict_SetItemString( fpData, iTer->c_str(), pList );
      Py_DECREF( pList );
    }
  // Done can now be cleared
  PyObject_CallFunctionObjArgs( fpResetFunction, fpData, NULL );
  PyToRIDS();
}

void
AnalysisScript::PyToRIDS()
{
  const RIDS::ChannelList& channelList = DataSelector::GetInstance().GetChannelList();

  fEvent = RIDS::Event( fTypes.size() );
  RIDS::Source source( fTypes.size() );
  for( size_t iType = 0; iType < fTypes.size(); iType++ )
    {
      PyObject* pList = PyDict_GetItemString( fpData, fTypes[iType].c_str() );
      RIDS::Type type;
      for( size_t iChannel = 0; iChannel < channelList.GetChannelCount(); iChannel++ )
        {
          const double data = PyFloat_AsDouble( PyList_GetItem( pList, iChannel ) );
          if( data > 0.0 )
            type.AddChannel( iChannel, data );
        }
      source.SetType( iType, type );
    }  
  fEvent.SetSource( 0, source );
}

void
AnalysisScript::ProcessEvent( const RIDS::Event& event )
{
  const RIDS::ChannelList& channelList = DataSelector::GetInstance().GetChannelList();

  // First convert the event structure into a python structure
  PyObject* pEvent = PyDict_New();
  const vector<string> sources = RIDS::Event::GetSourceNames();
  for( size_t iSource = 0; iSource < sources.size() - 1; iSource++ )
    {
      PyObject* pSource = PyDict_New();
      const vector<string> types = RIDS::Event::GetTypeNames( iSource );
      for( size_t iType = 0; iType < types.size(); iType++ )
        {
          PyObject* pList = PyList_New( channelList.GetChannelCount() );
          for( size_t iChannel = 0; iChannel < channelList.GetChannelCount(); iChannel++ )
            PyList_SetItem( pList, iChannel, PyFloat_FromDouble( -1.0 ) );
          const vector<RIDS::Channel> hits = DataSelector::GetInstance().GetData( iSource, iType );
          for( vector<RIDS::Channel>::const_iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
            PyList_SET_ITEM( pList, iTer->GetID(), PyFloat_FromDouble( iTer->GetData() ) ); // It is safe to lose the None
          PyDict_SetItemString( pSource, types[iType].c_str(), pList );
          Py_DECREF( pList );
        }
      PyDict_SetItemString( pEvent, sources[iSource].c_str(), pSource );
      Py_DECREF( pSource );
    }
  // Can now call the function
  PyObject_CallFunctionObjArgs( fpEventFunction, pEvent, fpData, NULL );
  Py_DECREF( pEvent );
  PyToRIDS();
}
