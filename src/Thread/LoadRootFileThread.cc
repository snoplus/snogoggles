#include <RAT/DS/Root.hh>
#include <RAT/DS/Run.hh>
using namespace RAT;

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <sstream>
#include <iostream>
using namespace std;

#include <Viewer/LoadRootFileThread.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;

void
LoadRootFileThread::Run()
{
  DataStore& events = DataStore::GetInstance();

  if( fTree == NULL )
    {
      LoadRootFile();
      events.SetRun( fRun );
      fTree->GetEntry( fMCEvent );
      events.AddDS( fDS );
      fSemaphore.Signal();
      fMCEvent++;
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
      events.AddDS( fDS );
      fMCEvent++;
      cout << "Loaded " << fMCEvent << " events." << endl;
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
