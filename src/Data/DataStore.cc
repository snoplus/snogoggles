#include <RAT/DS/Run.hh>
#include <RAT/DS/Root.hh>

#include <iostream>
using namespace std;

#include <Viewer/DataStore.hh>
#include <Viewer/RIDS/Event.hh>
using namespace Viewer;

DataStore::DataStore()
{
  fWriteIndex = 0;
  fReadIndex = 0;
  fEvent = NULL;
  fRun = NULL;
  fEvents.resize( 5000, NULL );
  fChanged = true;
}

void
DataStore::Initialise()
{
  Lock lock( fLock );
  fEvent = new RIDS::Event( *fEvents[0] );
  fScriptData.Load( "Default" );
}

DataStore::~DataStore()
{
  for( unsigned int uLoop = 0; uLoop < fEvents.size(); uLoop++ )
    delete fEvents[uLoop];
  fEvents.clear();
  delete fRun, fEvent;
}

void 
DataStore::SetRun( RAT::DS::Run* rRun )
{
  Lock lock( fLock );
  fRun = new RAT::DS::Run( *rRun );
}

bool
DataStore::AddDS( RAT::DS::Root* rDS )
{
  if( fLock.TryLock() == true )
    {
      delete fEvents[fWriteIndex];
      fEvents[fWriteIndex] = new RIDS::Event( *rDS, 0 ); // Always add 0, (may only be a mc event)
      fWriteIndex = (++fWriteIndex) % fEvents.size(); // Roll over
      for( unsigned int iEV = 1; iEV < rDS->GetEVCount(); iEV++ )
        {
          delete fEvents[fWriteIndex];
          fEvents[fWriteIndex] = new RIDS::Event( *rDS, iEV );
          fWriteIndex = (++fWriteIndex) % fEvents.size(); // Roll over
        }
      fLock.Unlock();
      return true;
    }
  return false;  
}

void 
DataStore::Latest()
{
  Lock lock( fLock );
  if( fWriteIndex == 0 )
    fReadIndex = fEvents.size() - 1;
  else
    fReadIndex = ( fWriteIndex - 1 ) % fEvents.size();
  delete fEvent;
  fEvent = new RIDS::Event( *fEvents[fReadIndex] );
  fScriptData.ProcessEvent( *fEvent );
  fChanged = true;
}

void 
DataStore::Next()
{
  Lock lock( fLock );
  fReadIndex = ++fReadIndex % fEvents.size();
  // Return to the previous event
  if( fEvents[fReadIndex] == NULL )
    {
      fReadIndex = 0;
    }
  delete fEvent;
  fEvent = new RIDS::Event( *fEvents[fReadIndex] );
  fScriptData.ProcessEvent( *fEvent );
  fChanged = true;
}

void 
DataStore::Prev()
{
  Lock lock( fLock );
  if( fReadIndex == 0 )
    fReadIndex = fEvents.size() - 1;
  else
    fReadIndex = --fReadIndex % fEvents.size();
  if( fEvents[fReadIndex] == NULL)
    fReadIndex = fWriteIndex - 1;
  delete fEvent;
  fEvent = new RIDS::Event( *fEvents[fReadIndex] );
  fScriptData.ProcessEvent( *fEvent );
  fChanged = true;
}

const int 
DataStore::GetBufferSize() 
{
  return  fEvents.size();
}

const int 
DataStore::GetBufferRead() 
{
  return  fReadIndex;
}

const int 
DataStore::GetBufferWrite() 
{
  return  fWriteIndex;
}



vector<RIDS::PMTHit> 
DataStore::GetHitData( RIDS::EDataSource source ) const
{
  if( source == RIDS::eScript )
    return fScriptData.GetHitData();
  else
    return GetCurrentEvent().GetHitData( source );
}
