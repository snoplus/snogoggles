#include <Viewer/EventData.hh>
using namespace Viewer;

#include <RAT/DS/Root.hh>
using namespace RAT;

EventData* EventData::fsEventData = NULL;

EventData::EventData()
{
  fCurrentEvent = NULL;
  fCurrentMC = NULL;
  fRun = NULL;
  fCurrentID = -1;
}

EventData::~EventData()
{
  for( unsigned int uLoop = 0; uLoop < fEVs.size(); uLoop++ )
    delete fEVs[uLoop];
  fEVs.clear();
  delete fRun;
}

void
EventData::NextEV()
{
  Lock lock( fLock );
  fCurrentID++;
  if( fCurrentID >= fEVs.size() )
    fCurrentID--;
  fCurrentEvent = fEVs[fCurrentID];
  if( !fMCs.empty() )
    fCurrentMC = fMCs[ fEVToMC[fCurrentID] ];
  return;
}

void
EventData::PreviousEV()
{
  Lock lock( fLock );
  fCurrentID--;
  if( fCurrentID < 0 )
    fCurrentID++;
  fCurrentEvent = fEVs[fCurrentID];  
  if( !fMCs.empty() )
    fCurrentMC = fMCs[ fEVToMC[fCurrentID] ];
  return;
}

bool
EventData::AddEV(
		 DS::EV* ev,
		 int mcEvent )
{
  if( fLock.TryLock() == true )
    {
      DS::EV* nEV = new DS::EV( *ev );
      fEVs.push_back( nEV );
      fEVToMC[ fEVs.size() - 1 ] = mcEvent;
      fLock.Unlock();
    }
  else
    return false;
}

bool
EventData::AddMC(
		 DS::MC* ev )
{
  if( fLock.TryLock() == true )
    {
      DS::MC* nMC = new DS::MC( *ev );
      fMCs.push_back( nMC );
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
    NextEV();
  return fCurrentEvent;    
}

DS::MC*
EventData::GetCurrentMC()
{
  if( fCurrentMC == NULL )
    NextEV();
  return fCurrentMC;    
}
