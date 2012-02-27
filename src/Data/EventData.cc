#include <iostream>
using namespace std;

#include <Viewer/EventData.hh>
using namespace Viewer;

EventData::EventData()
{
  fWriteIndex = 0;
  fDSIndex = 0;
  fDS = NULL;
  fRun = NULL;
  fEVIndex = 0;
  fEvents.resize( 5000, NULL );
}

void
EventData::Initialise()
{
  fDS = new RAT::DS::Root( *fEvents[0] );
}

EventData::~EventData()
{
  for( unsigned int uLoop = 0; uLoop < fEvents.size(); uLoop++ )
    delete fEvents[uLoop];
  fEvents.clear();
  delete fRun, fDS;
}

void 
EventData::SetRun( RAT::DS::Run* rRun )
{
  Lock lock( fLock );
  fRun = new RAT::DS::Run( *rRun );
}

bool
EventData::AddDS( RAT::DS::Root* rDS )
{
  if( fLock.TryLock() == true )
    {
      RAT::DS::Root* nDS = new RAT::DS::Root( *rDS );
      nDS->SetRunHere( fRun );
      if( nDS->GetEVCount() == 0 ) // Temp safety, will need some thought.
	nDS->AddNewEV();
      if( fEvents[fWriteIndex] != NULL )
	delete fEvents[fWriteIndex];
      fEvents[fWriteIndex] = nDS;
      fWriteIndex = (++fWriteIndex) % fEvents.size(); // Roll over
      fLock.Unlock();
      return true;
    }
  return false;  
}

void 
EventData::Latest()
{
  Lock lock( fLock );
  if( fWriteIndex == 0 )
    fDSIndex = fEvents.size() - 1;
  else
    fDSIndex = ( fWriteIndex - 1 ) % fEvents.size();
  fDS = new RAT::DS::Root( *fEvents[fDSIndex] );
  fEVIndex = 0;
}

void 
EventData::Next()
{
  Lock lock( fLock );
  fDSIndex = ++fDSIndex % fEvents.size();
  // Return to the previous event
  if( fEvents[fDSIndex] == NULL )
    {
      fDSIndex = 0;
    }
  fDS = new RAT::DS::Root( *fEvents[fDSIndex] );
  fEVIndex = 0;
}

void 
EventData::Prev()
{
  Lock lock( fLock );
  if( fDSIndex == 0 )
    fDSIndex = fEvents.size() - 1;
  else
    fDSIndex = --fDSIndex % fEvents.size();
  if( fEvents[fDSIndex] == NULL)
    fDSIndex = fWriteIndex - 1;
  fDS = new RAT::DS::Root( *fEvents[fDSIndex] );
  fEVIndex = 0;
}

