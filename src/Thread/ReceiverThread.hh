////////////////////////////////////////////////////////////////////////
/// \class ReceiverThread
///
/// \brief Accepts Packed ROOT events from a dispatcher
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     23/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail Receive and load Packed ROOT events.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ReceiverThread__
#define __Viewer_ReceiverThread__

#include <avalanche.hpp>

#include <Viewer/Thread.hh>

#include <string>

#include <TTree.h>
#include <TFile.h>
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

class ReceiverThread : public Thread
{
public:
  inline ReceiverThread( const std::string& port, Semaphore& semaphore );
  
  virtual ~ReceiverThread() {};
  
  virtual void
  Run();
private:
  /// Prevent usage
  void Receiver();

  std::string fPort;
  int fNumReceivedEvents;
  Semaphore& fSemaphore;

  avalanche::client fClient;
  // Temp below, (must load a DS::Run from somewhere - need PMT positions)
  void LoadRootFile();
  TFile* fFile;
  TTree* fTree;
  TTree* fRunTree;
  RAT::DS::Root* fDS;
  RAT::DS::Run* fRun;
};

ReceiverThread::ReceiverThread( const std::string& port, Semaphore& semaphore )
  : fSemaphore( semaphore ), fNumReceivedEvents(0), fPort( port )
{
  fRun = NULL;
}

} //::Viewer

#endif
