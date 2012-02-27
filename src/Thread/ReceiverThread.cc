#include <RAT/DS/EV.hh>
#include <RAT/DS/PMTProperties.hh>
#include <RAT/DS/Run.hh>
#include <RAT/Pack.hh>
using namespace RAT;

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <iostream>
using namespace std;

#include <Viewer/ReceiverThread.hh>
#include <Viewer/EventData.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;

ReceiverThread::ReceiverThread( const std::string& port, 
				Semaphore& semaphore,
				bool goodBuilder )
  : fSemaphore( semaphore ), fPort( port ), fNumReceivedEvents(0), fGoodBuilder( goodBuilder )
{

}

void
ReceiverThread::Initialise()
{
  // Must load a DS run for the PMT Positions (replace this with db access when possible...)
  LoadRunTree();
  fClient.addDispatcher( fPort.c_str() );
  cout << "Listening on " << fPort << endl;
}

void
ReceiverThread::Run()
{
  RAT::DS::PackedEvent* event = NULL;
  if( fGoodBuilder ) // Events come as PackedRec types
    {
      RAT::DS::PackedRec* rec = (RAT::DS::PackedRec*) fClient.recv();
      if( rec ) // avalanche is non-blocking
	event = dynamic_cast<RAT::DS::PackedEvent*> (rec->Rec);
    }
  else // Events come as PackedEvent types
    {
      event = (RAT::DS::PackedEvent*) fClient.recv();
    }
  if( event != NULL ) // avalanche is non-blocking
    {
      cout << "Got an event " << event->NHits << endl;
      RAT::DS::Root* rDS = RAT::Pack::UnpackEvent( event, NULL, NULL );
      EventData& events = EventData::GetInstance();
      events.AddDS( rDS );
      fNumReceivedEvents++;
      if( fNumReceivedEvents == 1 )
	fSemaphore.Signal();
      delete rDS;
      delete event;
    }
}

void
ReceiverThread::LoadRunTree()
{
  TFile* file = new TFile( "Temp.root", "READ" );
  TTree* runTree = (TTree*)file->Get( "runT" );
  RAT::DS::Run* rRun = new RAT::DS::Run();
  runTree->SetBranchAddress( "run", &rRun );
  runTree->GetEntry();

  EventData& events = EventData::GetInstance();
  events.SetRun( rRun );
  file->Close();
  delete file;
  delete rRun;
}
