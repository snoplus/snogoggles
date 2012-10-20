////////////////////////////////////////////////////////////////////////
/// \class LoadZdabFileThread
///
/// \brief   Loads the Zdab files
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     20/10/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Load events
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_LoadZdabFileThread__
#define __Viewer_LoadZdabFileThread__

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

namespace ratzdab
{
  class zdabfile;
}

namespace Viewer
{
  class Semaphore;

class LoadZdabFileThread : public Thread
{
public:
  inline LoadZdabFileThread( const std::string& fileName, Semaphore& semaphore );
  
  virtual ~LoadZdabFileThread() {};
  
  virtual void
  Run();
private:
  /// Must get the run tree from a root file to get the PMTProperties
  void LoadRootFile();

  /// Loads the next event if possible, returns false if no more events
  bool LoadNextEvent();

  std::string fFileName;

  int fMCEvent;
  Semaphore& fSemaphore;

  /// Main Zdab file to load from
  ratzdab::zdabfile* fFile;

  /// Root file part for the PMTProperties 
  TFile* fRootFile;
  TTree* fRunTree;
  RAT::DS::Run* fRun;
};

LoadZdabFileThread::LoadZdabFileThread( const std::string& fileName, Semaphore& semaphore )
  : fSemaphore( semaphore ), fFileName( fileName )
{ 
  fFile = NULL; 
  fRootFile = NULL;
  fRun = NULL; 
  fMCEvent = 0; 
} 

} //::Viewer

#endif
