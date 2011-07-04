#include <Viewer/Mutex.hh>
using namespace Viewer;


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

Lock::Lock( Mutex& mutex )
  : fMutex( mutex )
{
  fMutex.Lock();
}

Lock::~Lock()
{
  fMutex.Unlock();
}
