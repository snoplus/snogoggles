#include <RAT/DS/Root.hh>
#include <RAT/DS/Run.hh>
using namespace RAT;

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <sstream>
using namespace std;

#include <Viewer/LoadRootFileThread.hh>
#include <Viewer/EventData.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;

void
LoadRootFileThread::Run()
{
  EventData& events = EventData::GetInstance();
  if( fTree == NULL )
    {
      LoadRootFile();
      events.SetRun( fRun );
      fTree->GetEntry( fMCEvent );
      if( fDS->ExistMC() )
	events.AddMC( fDS->GetMC() );
      for( int iEV = 0; iEV < fDS->GetEVCount(); iEV++ )
	{
	  events.AddEV( fDS->GetEV( iEV ), fMCEvent );
	}
      fMCEvent++;
      fSemaphore.Signal();
      return;
    }
  if( fMCEvent >= fTree->GetEntries() )
    {
      fFile->Close();
      delete fFile;
      delete fDS;
      delete fRun;
      Kill();
    }
  else
    {
      fTree->GetEntry( fMCEvent );
      if( fDS->ExistMC() )
	events.AddMC( fDS->GetMC() );
      for( int iEV = 0; iEV < fDS->GetEVCount(); iEV++ )
	{
	  events.AddEV( fDS->GetEV( iEV ), fMCEvent );
	}
      fMCEvent++;
    }
}

void
LoadRootFileThread::LoadRootFile()
{
  fFile = new TFile( fFileName.c_str(), "READ" );
 
  fTree = (TTree*)fFile->Get( "T" ); 
  fDS = new RAT::DS::Root();
  fTree->SetBranchAddress( "ds", &fDS );

  fRunTree = (TTree*)fFile->Get( "runT" ); 
  fRun = new RAT::DS::Run();
  fRunTree->SetBranchAddress( "run", &fRun );
  fRunTree->GetEntry();
}
