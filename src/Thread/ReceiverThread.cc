// PHIL: REWRITE THIS AFTER ANDY'S CONVERSION FUNCTIONS ADDITION!


#include <RAT/DS/PackedEvent.hh>
#include <RAT/DS/EV.hh>
#include <RAT/DS/PMTCal.hh>
#include <RAT/DS/PMTProperties.hh>
//#include <RAT/BitManip.hh>
#include <RAT/DS/Root.hh>
#include <RAT/DS/Run.hh>
using namespace RAT;

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <sstream>
#include <iostream>
using namespace std;

#include <Viewer/ReceiverThread.hh>
#include <Viewer/EventData.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;

#include <avalanche.hpp>

// Required as the BitManip file is hard to include, TODO fix the BitManip file
int GetBits(int arg, int loc, int n)
{
  int shifted = arg >> loc;
  // Select the first (least significant) n of those bits
  int mask = ((ULong64_t)1 << n) - 1;
  int value = shifted & mask;
  return value;
}

void
ReceiverThread::Run()
{
  // Must load a DS run for the PMT Positions (replace this with db access when possible...)
  EventData& events = EventData::GetInstance();
  if( fNumReceivedEvents == 0 )
    {
      LoadRootFile();
      events.SetRun( fRun );
      fFile->Close();
      delete fFile;
      delete fDS;
      delete fRun;
    }

  // create a client, listening for objects
  avalanche::client client(fPort.c_str());
  // receive RAT::DS::PackedRec objects, blocks until recieves packet
  cout << "Listening" << endl;
  RAT::DS::PackedRec* rec = (RAT::DS::PackedRec*) client.recvObject(RAT::DS::PackedRec::Class());
  if( rec->RecordType == 1 ) //Detector event (why not enum?)
    {
      cout << "Got an event" << endl;
      RAT::DS::PackedEvent* eventRecord = reinterpret_cast<RAT::DS::PackedEvent*>( rec->Rec );
      // Now build an EV event, (my temp fix)
      RAT::DS::EV* rEV = new RAT::DS::EV();
      rEV->SetEventID( GetBits( eventRecord->MTCInfo[3], 0, 24 ) );
      // Now add the PMT hits
      for( unsigned int uPMT = 0; uPMT < eventRecord->PMTBundles.size(); uPMT++ )
	{
	  RAT::DS::PMTBundle bundle = eventRecord->PMTBundles[uPMT];
	  RAT::DS::PMTCal* rPMTCal = rEV->AddNewPMTCal( RAT::DS::PMTProperties::NORMAL ); // Not really a PMTCal...
	  int lcn = -1;
	  int icrate = GetBits(bundle.Word[0], 21, 5);
	  int icard = GetBits(bundle.Word[0], 26, 4);
	  int ichan = GetBits(bundle.Word[0], 16, 5);
	  lcn = 512*icrate + 32*icard + ichan;
	  int time = GetBits( bundle.Word[2], 16, 12 );
	  // Temp flip bit follows (must be replaced)
	  if( time & ( 1 << 11 ) )
	    time = time & ~( 1 << 11 );
	  else
	    time = time | ( 1 << 11 );
	  rPMTCal->SetID( lcn );
	  rPMTCal->SetsPMTt( time / 10 + 220 ); // Bad temp fix
	}
      
      events.AddEV( rEV, fNumReceivedEvents );
      fNumReceivedEvents++;
      if( fNumReceivedEvents == 1 )
      	fSemaphore.Signal();
      delete rec;
    }
 
}

void
ReceiverThread::LoadRootFile()
{
  fFile = new TFile( "Temp.root", "READ" );
 
  fTree = (TTree*)fFile->Get( "T" ); 
  fDS = new RAT::DS::Root();
  fTree->SetBranchAddress( "ds", &fDS );

  fRunTree = (TTree*)fFile->Get( "runT" ); 
  fRun = new RAT::DS::Run();
  fRunTree->SetBranchAddress( "run", &fRun );
  fRunTree->GetEntry();
}
