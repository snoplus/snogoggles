////////////////////////////////////////////////////////////////////////
/// \class ReceiverThread
///
/// \brief Accepts Packed ROOT events from a dispatcher
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     23/02/12 : P.Jones - First Revision, new file. \n
///     27/02/12 : P.Jones - Second Revision, stability improvements. \n
///     25/03/14 : P.Jones - RIDS Refactor. \n
///
/// \detail Setup a avalanche client to receive packed ROOT events from
///         a suitable dispatcher.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_ReceiverThread__
#define __Viewer_ReceiverThread__

#include <Viewer/Thread.hh>

#include <string>

namespace RAT
{
namespace DS
{
  class Root;
}
}

namespace ratzdab
{
  class dispatch;
}

namespace Viewer
{
  class Semaphore;

class ReceiverThread : public Thread
{
public:
  /// Construct the Receiver thread, requires the port to use and a semaphore to signal data has arrived.
  ReceiverThread( const std::string& port, 
                  Semaphore& semaphore );
  /// Destructor, closes the avalanche client etc...
  virtual ~ReceiverThread();
  /// Run function, called by the thread
  virtual void Run();

private:
  /// Initialise the receiving socket
  void Initialise();
  /// Prevent usage outside of the calls
  void Receiver();
  /// Initialise RIDS i.e define the data 
  void InitialiseRIDS();
  /// Build a RIDS event from the currently received event
  void BuildRIDSEvent( RAT::DS::Root* rDS );

  ratzdab::dispatch* fReceiver; /// < The ratzdab dispatcher reciever and converter
  int fNumReceivedEvents; /// < The current number of recieved events
  Semaphore& fSemaphore; /// < The semaphore to signal events have arrrived
  std::string fPort; /// < The avalanche port
};

} //::Viewer

#endif
