////////////////////////////////////////////////////////////////////////
/// \class Viewer::Mutex, Lock
///
/// \brief   Mutex class
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     04/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Mutex, blocking (or not) locks between threads. These are 
///          basically the same as sfml threads/mutexes but have a trylock.
///
////////////////////////////////////////////////////////////////////////


#ifndef Mutex_hh
#define Mutex_hh

#include <pthread.h>

namespace Viewer
{

class Mutex
{
public:
  Mutex();
  ~Mutex();

  bool
  TryLock();

  void
  Lock();

  void
  Unlock();
private:
  pthread_mutex_t fMutex; /// <Mutex lock itself
};

class Lock
{
public:
  Lock(
       Mutex& mutex );

  ~Lock();
private:
  Mutex& fMutex;
};

} // ::Viewer

#endif
