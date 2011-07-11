#include <Viewer/EventData.hh>
using namespace Viewer;

#include <RAT/DS/Root.hh>
using namespace RAT;

EventData* EventData::fsEventData = NULL;

EventData::EventData()
{
  fCurrentEvent = NULL;
  fRun = NULL;
  fCurrentID = 0;
}

EventData::~EventData()
{
  for( unsigned int uLoop = 0; uLoop < fEVs.size(); uLoop++ )
    delete fEVs[uLoop];
  fEVs.clear();
  delete fRun;
}

DS::EV*
EventData::NextEV()
{
  Lock lock( fLock );
  fCurrentID++;
  if( fCurrentID >= fEVs.size() )
    fCurrentID--;
  fCurrentEvent = fEVs[fCurrentID];
  return fCurrentEvent;
}

DS::EV*
EventData::PreviousEV()
{
  Lock lock( fLock );
  fCurrentID--;
  if( fCurrentID < 0 )
    fCurrentID++;
  fCurrentEvent = fEVs[fCurrentID];
  return fCurrentEvent;
}

bool
EventData::AddEV(
	      DS::EV* ev )
{
  if( fLock.TryLock() == true )
    {
      DS::EV* nEV = new DS::EV( *ev );
      fEVs.push_back( nEV );
      fLock.Unlock();
    }
  else
    return false;
}

void
EventData::SetRun(
		  DS::Run* run ) 
{ 
  fRun = new RAT::DS::Run( *run ); 
}

DS::EV*
EventData::GetCurrentEV()
{
  if( fCurrentEvent == NULL )
    {
      Lock lock( fLock );
      fCurrentEvent = fEVs[fCurrentID];
    }
  return fCurrentEvent;    
}
