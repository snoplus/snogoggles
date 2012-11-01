#include <RAT/DS/Run.hh>
#include <RAT/DS/Root.hh>

#include <iostream>
using namespace std;

#include <Viewer/DataStore.hh>
#include <Viewer/PythonScripts.hh>
#include <Viewer/RIDS/Event.hh>
using namespace Viewer;

size_t AdjustIndex( const size_t currentIndex, const size_t limit, const int change )
{
  if( change > 0 )
    return ( currentIndex + change ) % limit;
  else
    {
      if( currentIndex <= -change )
        return limit + change - currentIndex;
      else
        return currentIndex + change;
    }
}


DataStore::DataStore()
  : fInputBuffer( 5000 ) 
{ 
  fEvents.resize( 5000, NULL ); 
  fWrite = 0;
  fRead = 0;
  fEventsAdded = 1;
  fEvent = NULL;
  fRun = NULL;
  fChanged = true;
  fSelecting = false;
  fAnalysing = false;
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
      fEventsAdded++;
      delete fEvents[fWrite];
      fEvents[fWrite] = currentEvent;
      fWrite = ( fWrite + 1 ) % fEvents.size();
    }
}

void 
DataStore::Latest()
{
  size_t prev = AdjustIndex( fWrite, fEvents.size(), -1 );
  size_t eventsChecked = 0;
  while( eventsChecked < fEvents.size() )
    {
      if( SelectEvent( fEvents[prev] ) )
        {
          ChangeEvent( prev );
          return;
        }
      prev = AdjustIndex( prev, fEvents.size(), -1 );
      eventsChecked++;
    }
}

void 
DataStore::Next( const size_t step )
{
  size_t next = AdjustIndex( fRead, fEvents.size(), +1 );
  size_t eventsChecked = 0;
  size_t eventsStepped = 0; // Good events stepped over
  while( eventsChecked < fEvents.size() )
    {
      if( SelectEvent( fEvents[next] ) )
        {
          eventsStepped++;
          if( eventsStepped == step )
            {
              ChangeEvent( next );
              return;
            }
        }
      next = AdjustIndex( next, fEvents.size(), +1 );
    }
}

void 
DataStore::Prev( const size_t step )
{
  size_t prev = AdjustIndex( fRead, fEvents.size(), -1 );
  size_t eventsChecked = 0;
  size_t eventsStepped = 0; // Good events stepped over
  while( eventsChecked < fEvents.size() )
    {
      if( SelectEvent( fEvents[prev] ) )
        {
          eventsStepped++;
          if( eventsStepped == step )
            {
              ChangeEvent( prev );
              return;
            }
        }
      prev = AdjustIndex( prev, fEvents.size(), -1 );
    }
}

bool
DataStore::SelectEvent( RIDS::Event* event )
{
  if( event == NULL )
    return false;
  if( fSelecting )
    return PythonScripts::GetInstance().GetEventSelection().ProcessEvent( *event );
  else // Return true if event selection is off
    return true;
}

void
DataStore::ChangeEvent( const size_t eventID )
{
  if( fRead == eventID ) 
    return; // Nothing to change
  fRead = eventID;
  delete fEvent;
  fEvent = new RIDS::Event( *fEvents[fRead] );
  fChanged = true;
  if( fAnalysing )
    PythonScripts::GetInstance().GetAnalysis().ProcessEvent( *fEvent );
}

vector<RIDS::PMTHit> 
DataStore::GetHitData( RIDS::EDataSource source ) const
{
  if( source == RIDS::eScript )
    return PythonScripts::GetInstance().GetAnalysis().GetHitData();
  else
    return GetCurrentEvent().GetHitData( source );
}
