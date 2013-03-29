#include <RAT/DS/Root.hh>
using namespace RAT;

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
using namespace std;

#include <Viewer/ReceiverThread.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>

#include <zdab_dispatch.hpp>

ReceiverThread::ReceiverThread( const std::string& port, 
                                Semaphore& semaphore )
  : fSemaphore( semaphore ), fPort( port ), fNumReceivedEvents(0)
{

}

ReceiverThread::~ReceiverThread()
{
  delete fReceiver;
}

void
ReceiverThread::Initialise()
{
  std::string subscribe = "w RAWDATA";
  fReceiver = new ratzdab::dispatch( fPort, subscribe );
  cout << "Listening on " << fPort << " for " << subscribe << endl;
  InitialiseRIDS();
}

void
ReceiverThread::InitialiseRIDS()
{
  vector< pair< string, vector< string > > > dataNames;
  vector<string> uncalTypes; uncalTypes.push_back( "TAC" ); uncalTypes.push_back( "QHL" ); uncalTypes.push_back( "QHS" ); uncalTypes.push_back( "QLX" );
  dataNames.push_back( pair< string, vector< string > >( "UnCal", uncalTypes ) );
  RIDS::Event::Initialise( dataNames );
}

void
ReceiverThread::Run()
{
  RAT::DS::Root* event = NULL;
  RAT::DS::Root* rec = (RAT::DS::Root*) fReceiver->next();
  if( rec ) // avalanche is non-blocking
    event = dynamic_cast<RAT::DS::Root*> (rec);
  if( event != NULL ) // avalanche is non-blocking
    {
      cout << "Event of run: " << dec << rec->GetRunID() << " with [";
      for( int iEV = 0; iEV < rec->GetEVCount(); iEV++ )
        cout << "0x" << hex << uppercase << rec->GetEV(iEV)->GetEventID();
      time_t now = time(0);
      struct tm* tm = localtime( &now );
      cout << "] events at " << dec << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec << endl;
      BuildRIDSEvent( event );
      fNumReceivedEvents++;
      if( fNumReceivedEvents == 1 )
        fSemaphore.Signal();
    }
  delete rec;
}

void 
ReceiverThread::BuildRIDSEvent( RAT::DS::Root* rDS )
{
  RAT::DS::EV* rEV = rDS->GetEV( 0 );
  RIDS::Source unCal( 4 );
  RIDS::Type tac, qhl, qhs, qlx;
  for( int iUnCal = 0; iUnCal < rEV->GetPMTUnCalCount(); iUnCal++ )
    {
      RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( iUnCal );
      tac.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetTime() );
      qhl.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetsQHL() );
      qhs.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetsQHS() );
      qlx.AddChannel( rPMTUnCal->GetID(), rPMTUnCal->GetsQLX() );
    }
  unCal.SetType( 0, tac );
  unCal.SetType( 1, qhl );
  unCal.SetType( 2, qhs );
  unCal.SetType( 3, qlx );
  RIDS::Event* event = new RIDS::Event();
  event->SetSource( 0, unCal );
  DataStore::GetInstance().AddEvent( event );
}
