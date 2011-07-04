#include <RAT/DS/Root.hh>
#include <RAT/DS/PMTProperties.hh>
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
      LoadRootFile( &fTree, &fDS, &fPMTList );
      events.SetPMTList( fPMTList );
      fTree->GetEntry( fMCEvent );
      for( int iEV = 0; iEV < fDS->GetEVCount(); iEV++ )
	{
	  events.AddEV( fDS->GetEV( iEV ) );
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
      Kill();
    }
  else
    {
      fTree->GetEntry( fMCEvent );
      for( int iEV = 0; iEV < fDS->GetEVCount(); iEV++ )
	{
	  events.AddEV( fDS->GetEV( iEV ) );
	}
      fMCEvent++;
    }
}

void
LoadRootFileThread::LoadRootFile(
				 TTree **tree,
				 RAT::DS::Root **rDS,
				 RAT::DS::PMTProperties **rPMTList )
{
  fFile = new TFile( fFileName.c_str(), "READ" );
  (*tree) = (TTree*)fFile->Get( "T" ); 
  TTree *runTree = (TTree*)fFile->Get( "runT" ); 
  
  *rDS = new RAT::DS::Root();

  (*tree)->SetBranchAddress( "ds", &(*rDS) );

  RAT::DS::Run* rRun = new RAT::DS::Run();

  runTree->SetBranchAddress( "run", &rRun );

  runTree->GetEntry();
  *rPMTList = rRun->GetPMTProp();
}
