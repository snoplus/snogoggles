////////////////////////////////////////////////////////////////////////
/// \class Mutex, Lock, Thread
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
#include <semaphore.h>

class Semaphore
{
public:
  Semaphore();
  ~Semaphore();

  void
  Wait();

  void
  Signal();
private:
#ifdef __APPLE__
  sem_t* fSemaphore;
#else
  sem_t fSemaphore;
#endif
};


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
  pthread_mutex_t fMutex; //! <Mutex lock itself
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
  TRun();
private:
  static void* 
  PosixCaller( void* arg );

  bool fRun; //! <If false then thread stops.
  pthread_t fPThread; //! <Posix thread handle for this...
};

#endif
