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
#include <Viewer/DataStore.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;

ReceiverThread::ReceiverThread( const std::string& port, 
                                Semaphore& semaphore )
  : fSemaphore( semaphore ), fPort( port ), fNumReceivedEvents(0)
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
  RAT::DS::PackedRec* rec = (RAT::DS::PackedRec*) fClient.recv();
  if( rec ) // avalanche is non-blocking
    event = dynamic_cast<RAT::DS::PackedEvent*> (rec->Rec);
  if( event != NULL ) // avalanche is non-blocking
    {
      cout << "Got an event " << event->NHits << endl;
      DataStore& events = DataStore::GetInstance();
      events.Add( event );
      fNumReceivedEvents++;
      if( fNumReceivedEvents == 1 )
        fSemaphore.Signal();
    }
  delete rec;
}

void
ReceiverThread::LoadRunTree()
{
  TFile* file = new TFile( "Temp.root", "READ" );
  TTree* runTree = (TTree*)file->Get( "runT" );
  RAT::DS::Run* rRun = new RAT::DS::Run();
  runTree->SetBranchAddress( "run", &rRun );
  runTree->GetEntry();

  DataStore& events = DataStore::GetInstance();
  events.SetRun( rRun );
  file->Close();
  delete file;
  delete rRun;
}
