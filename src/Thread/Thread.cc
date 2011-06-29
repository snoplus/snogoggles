
#include <Thread.hh>
#include <iostream>

////////////////////////////////////////////////////////////////////////
/// Semaphore functions
////////////////////////////////////////////////////////////////////////
Semaphore::Semaphore()
{
  // Will need to worry about apple naming soon...
#ifdef __APPLE__
  fSemaphore = sem_open( "Sema", O_CREAT | O_EXCL, 0644, 0 );
#else
  sem_init( &fSemaphore, 0, 0 );
#endif
}

Semaphore::~Semaphore()
{
#ifdef __APPLE__
  //fSemaphore = sem_unlink( "Sema" );
  sem_unlink( "Sema" );
#else
  sem_destroy( &fSemaphore );
#endif
}

void
Semaphore::Wait()
{
#ifdef __APPLE__
  sem_wait( fSemaphore );
#else
  sem_wait( &fSemaphore );
#endif
}

void
Semaphore::Signal()
{
#ifdef __APPLE__
  sem_post( fSemaphore );
#else
  sem_post( &fSemaphore );
#endif
}

////////////////////////////////////////////////////////////////////////
/// Mutex functions
////////////////////////////////////////////////////////////////////////

Mutex::Mutex()
{
  pthread_mutex_init( &fMutex, NULL );
}

Mutex::~Mutex()
{
  pthread_mutex_destroy( &fMutex );
}

bool
Mutex::TryLock()
{
  return pthread_mutex_trylock( &fMutex ) == 0;
}

void
Mutex::Lock()
{
  pthread_mutex_lock( &fMutex );
}

void
Mutex::Unlock()
{
  pthread_mutex_unlock( &fMutex );
}

////////////////////////////////////////////////////////////////////////
/// Lock functions
////////////////////////////////////////////////////////////////////////

Lock::Lock( Mutex& mutex )
  : fMutex( mutex )
{
  fMutex.Lock();
}

Lock::~Lock()
{
  fMutex.Unlock();
}

////////////////////////////////////////////////////////////////////////
/// Thread functions
////////////////////////////////////////////////////////////////////////

Thread::Thread()
{
  fRun = true;
  pthread_create( &fPThread, NULL, Thread::PosixCaller, reinterpret_cast<void*>( this ) );
}

Thread::~Thread()
{

}

void* 
Thread::PosixCaller( void* arg )
{
  Thread* threadInstance = reinterpret_cast<Thread*>( arg );
  threadInstance->TRun();
  return NULL;
}

void
Thread::KillAndWait()
{
  fRun = false;
  Wait();
}

void
Thread::Kill()
{
  fRun = false;
}

void
Thread::Wait()
{
  pthread_join( fPThread, NULL );
}

void
Thread::TRun()
{
  while( fRun )
    Run();
  pthread_exit(NULL);
}

void
Thread::Run()
{

}
