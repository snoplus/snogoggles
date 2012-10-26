#include <RAT/DS/EV.hh>
#include <RAT/DS/PMTProperties.hh>
#include <RAT/DS/Run.hh>
#include <RAT/Pack.hh>
using namespace RAT;

#ifdef __ZDAB
#include <zdab_dispatch.hpp>
#endif

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
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

ReceiverThread::~ReceiverThread()
{
  delete fReceiver;
}

void
ReceiverThread::Initialise()
{
#ifdef __ZDAB
  // Must load a DS run for the PMT Positions (replace this with db access when possible...)
  LoadRunTree();
  std::string subscribe = "w RAWDATA";
  fReceiver = new ratzdab::dispatch( fPort, subscribe );
  cout << "Listening on " << fPort << " for " << subscribe << endl;
#endif
}

void
ReceiverThread::Run()
{
#ifdef __ZDAB
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
      DataStore& events = DataStore::GetInstance();
      events.Add( event );
      fNumReceivedEvents++;
      if( fNumReceivedEvents == 1 )
        fSemaphore.Signal();
    }
  delete rec;
#else
  Kill();
#endif
}

void
ReceiverThread::LoadRunTree()
{
  stringstream fileLocation;
  fileLocation << getenv( "VIEWERROOT" ) << "/Temp.root";
  TFile* file = new TFile( fileLocation.str().c_str(), "READ" );
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
