////////////////////////////////////////////////////////////////////////
/// \class LoadRootFileThread
///
/// \brief   Loads the ROOT files
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     04/11 : P.Jones - First Revision, new file. \n
///     25/03/14 : P.Jones - RIDS Refactor. \n
///
/// \detail  Load events from a root file.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_LoadRootFileThread__
#define __Viewer_LoadRootFileThread__

#include <TTree.h>
#include <TFile.h>

#include <string>

#include <Viewer/Thread.hh>

namespace RAT
{
namespace DS
{
  class Root;
  class Run;
}
}

namespace Viewer
{
  class Semaphore;

class LoadRootFileThread : public Thread
{
public:
  inline LoadRootFileThread( const std::string& fileName, Semaphore& semaphore );
  
  virtual ~LoadRootFileThread() {};
  
  virtual void
  Run();
private:
  /// Load the root file and set the fDS and fRun pointers
  void LoadRootFile();
  /// Initialise the RIDS i.e. define what data exists
  void InitialiseRIDS();
  /// Build a single RIDS event from the current fDS event
  void BuildRIDSEvent();

  std::string fFileName;
  TFile* fFile;
  TTree* fTree;
  TTree* fRunTree;
  RAT::DS::Root* fDS;
  RAT::DS::Run* fRun;
  int fMCEvent;
  Semaphore& fSemaphore;
};

LoadRootFileThread::LoadRootFileThread( const std::string& fileName, Semaphore& semaphore )
  : fSemaphore( semaphore ), fFileName( fileName )
{ 
  fTree = NULL; 
  fDS = NULL; 
  fRun = NULL; 
  fMCEvent = 0; 
} 

} //::Viewer

#endif
