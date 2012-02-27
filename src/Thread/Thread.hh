////////////////////////////////////////////////////////////////////////
/// \class Mutex
///
/// \brief   Base class for threads
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     04/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All threads must derive from this, these are basically the
///          same as sfml threads/mutexes but have a trylock.
///
////////////////////////////////////////////////////////////////////////


#ifndef Thread_hh
#define Thread_hh

#include <pthread.h>

namespace Viewer
{

class Thread
{
public:
  Thread(); 

  ~Thread();

  void
  Wait();

  void
  KillAndWait();

  void
  Kill();

  virtual void
  Run();

  //private:
  void
  RunT();
protected:
  /// Initialise the thread (always will be run in the separate thread).
  virtual void
  Initialise();

private:
  static void* 
  PosixCaller( void* arg );

  bool fRun; /// <If false then thread stops.
  pthread_t fPThread; /// <Posix thread handle for this...
};

} //::Viewer

#endif
