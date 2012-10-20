#include <RAT/DS/Root.hh>
#include <RAT/DS/Run.hh>
using namespace RAT;

#include <zdab_file.hpp>

#include <TTree.h>
#include <TFile.h>
using namespace ROOT;

#include <sstream>
#include <iostream>
using namespace std;

#include <Viewer/LoadZdabFileThread.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Semaphore.hh>
using namespace Viewer;

void
LoadZdabFileThread::Run()
{
  DataStore& events = DataStore::GetInstance();

  if( fFile == NULL )
    {
      LoadRootFile();
      fFile = new ratzdab::zdabfile( fFileName.c_str() );
      LoadNextEvent();
      events.SetRun( fRun );
      fSemaphore.Signal();
      fMCEvent++;
      return;
    }
  bool success = LoadNextEvent();
  fMCEvent++;
  cout << "Loaded " << fMCEvent << " events." << endl;  
  if( !success )
    {
      delete fFile;
      fRootFile->Close();
      delete fRootFile;
      delete fRun;
      Kill();
    }
}

bool
LoadZdabFileThread::LoadNextEvent()
{
  try
    {
      TObject* record = fFile->next();
      if( record == NULL )
        return false;
      if( record->IsA() == RAT::DS::Root::Class() ) 
        {
          RAT::DS::Root* ds = new RAT::DS::Root( *reinterpret_cast<RAT::DS::Root*>( record ) );
          DataStore& events = DataStore::GetInstance();
          events.Add( ds );
          delete ds;
          return true;
        }
      else // Iterate through until an event is located
        return LoadNextEvent();
    }
  catch( ratzdab::unknown_record_error& e )
    {
      return LoadNextEvent(); // Carry on and try again...
    }
}

void
LoadZdabFileThread::LoadRootFile()
{
  stringstream fileLocation;
  fileLocation << getenv( "VIEWERROOT" ) << "/Temp.root";
  fRootFile = new TFile( fileLocation.str().c_str(), "READ" );
 
  fRunTree = (TTree*)fRootFile->Get( "runT" ); 
  fRun = new RAT::DS::Run();
  fRunTree->SetBranchAddress( "run", &fRun );
  fRunTree->GetEntry();
}
