#include <Viewer/Semaphore.hh>
using namespace Viewer;

Semaphore::Semaphore()
{
#ifdef __APPLE__
  fSemaphore = sem_open( "Sema", O_CREAT | O_EXCL, 0644, 0 ); //Must be hard coded name, or get Apple weirdness
#else
  sem_init( &fSemaphore, 0, 0 );
#endif
}

Semaphore::~Semaphore()
{
#ifdef __APPLE__
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
