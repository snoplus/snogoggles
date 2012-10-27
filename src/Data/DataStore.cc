#include <RAT/DS/Run.hh>
#include <RAT/DS/Root.hh>

#include <iostream>
using namespace std;

#include <Viewer/DataStore.hh>
#include <Viewer/PythonScripts.hh>
#include <Viewer/RIDS/Event.hh>
using namespace Viewer;

DataStore::DataStore()
  : fInputBuffer( 5000 ) 
{ 
  fEvents.resize( 5000, NULL ); 
  fWrite = 0;
  fRead = 0;
  fEvent = NULL;
  fRun = NULL;
  fChanged = true;
  fSelecting = true;
}

void
DataStore::Initialise()
{
  PythonScripts::GetInstance().Initialise();
  RIDS::Event* currentEvent = NULL;
  fInputBuffer.Pop( currentEvent ); // Guaranteed by semaphore to work
  fEvents[fWrite] = currentEvent;
  fWrite = ( fWrite + 1 ) % fEvents.size();
  fEvent = new RIDS::Event( *currentEvent );
  fChanged = true;
}

DataStore::~DataStore()
{
  Update();
  for( unsigned int uLoop = 0; uLoop < fEvents.size(); uLoop++ )
    delete fEvents[uLoop];
  fEvents.clear();
  delete fRun, fEvent;
}

void 
DataStore::SetRun( RAT::DS::Run* rRun )
{
  fRun = new RAT::DS::Run( *rRun );
}

bool
DataStore::Add( RAT::DS::Root* rDS )
{
  RIDS::Event* event = new RIDS::Event( *rDS, 0 );  // Always add 0, (may only be a mc event)
  bool added = fInputBuffer.Push( event );
  if( !added )
    return false;
  for( int iEV = 1; iEV < rDS->GetEVCount(); iEV++ )
    {
      event = new RIDS::Event( *rDS, iEV );
      if( !fInputBuffer.Push( event ) )
        return false;
    }
  return true;
}

void
DataStore::Update()
{
  // Called every frame, so inform of no changes
  fChanged = false;
  /// This will overwrite existing events
  RIDS::Event* currentEvent = NULL;
  while( fInputBuffer.Pop( currentEvent ) )
    {
      fEvents[fWrite] = currentEvent;
      fWrite = ( fWrite + 1 ) % fEvents.size();
    }
}

void 
DataStore::Latest()
{
  int prev = ( fWrite - 1 ) % fEvents.size();
  RIDS::Event* currentEvent = fEvents[prev];
  // Check test event is valid and ensure code does not circularly loop
  while( currentEvent != NULL && prev != fRead ) 
    {
      if( SelectEvent( *currentEvent ) )
        break; // Found an acceptable event
      prev = ( prev - 1 ) % fEvents.size();
      currentEvent = fEvents[prev];
    }
  fRead = prev;
  fEvent = new RIDS::Event( *fEvents[fRead] );
  fChanged = true;
}

void 
DataStore::Next()
{
  int next = ( fRead + 1 ) % fEvents.size();
  RIDS::Event* currentEvent = fEvents[next];
  // Check test event is valid and ensure code does not circularly loop
  while( currentEvent != NULL && next != fRead ) 
    {
      if( SelectEvent( *currentEvent ) )
        break; // Found an acceptable event
      next = ( next + 1 ) % fEvents.size();
      currentEvent = fEvents[next];
    }
  fRead = next;
  fEvent = new RIDS::Event( *fEvents[fRead] );
  fChanged = true;
}

void 
DataStore::Prev()
{
  int prev = ( fRead - 1 ) % fEvents.size();
  RIDS::Event* currentEvent = fEvents[prev];
  // Check test event is valid and ensure code does not circularly loop
  while( currentEvent != NULL && prev != fRead ) 
    {
      if( SelectEvent( *currentEvent ) )
        break; // Found an acceptable event
      prev = ( prev - 1 ) % fEvents.size();
      currentEvent = fEvents[prev];
    }
  fRead = prev;
  fEvent = new RIDS::Event( *fEvents[fRead] );
  fChanged = true;
}

bool
DataStore::SelectEvent( RIDS::Event& event )
{
  if( fSelecting )
    return PythonScripts::GetInstance().GetEventSelection().ProcessEvent( event );
  else // Return true if event selection is off
    return true;
}

vector<RIDS::PMTHit> 
DataStore::GetHitData( RIDS::EDataSource source ) const
{
  if( source == RIDS::eScript )
    return PythonScripts::GetInstance().GetAnalysis().GetHitData();
  else
    return GetCurrentEvent().GetHitData( source );
}
