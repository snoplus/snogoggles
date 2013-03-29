////////////////////////////////////////////////////////////////////////
/// \class LoadZdabFileThread
///
/// \brief   Loads the Zdab files
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     20/10/12 : P.Jones - First Revision, new file. \n
///     25/03/14 : P.Jones - RIDS Refactor. \n
///
/// \detail  Load events from a zdab file
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_LoadZdabFileThread__
#define __Viewer_LoadZdabFileThread__

#include <string>

#include <Viewer/Thread.hh>

namespace RAT
{
namespace DS
{
  class Root;
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
  /// Loads the next event if possible, returns false if no more events
  bool LoadNextEvent();
  /// Initialise RIDS i.e. define what data exists
  void InitialiseRIDS();
  /// Build a single RIDS event from a loaded event
  void BuildRIDSEvent( RAT::DS::Root* rDS );

  std::string fFileName;

  int fMCEvent;
  Semaphore& fSemaphore;

  /// Main Zdab file to load from
  ratzdab::zdabfile* fFile;
};

LoadZdabFileThread::LoadZdabFileThread( const std::string& fileName, Semaphore& semaphore )
  : fSemaphore( semaphore ), fFileName( fileName )
{ 
  fFile = NULL; 
  fMCEvent = 0; 
} 

} //::Viewer

#endif
