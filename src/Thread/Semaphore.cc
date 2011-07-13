#ifdef __APPLE__
#include <string>
using namespace std;
#endif

#include <Viewer/Semaphore.hh>
using namespace Viewer;

#ifdef __APPLE__
Semaphore::Semaphore( const string& name )
{
  fName = name;
  fSemaphore = sem_open( fName.c_str(), O_CREAT | O_EXCL, 0644, 0 );
}
#else
Semaphore::Semaphore()
{
  sem_init( &fSemaphore, 0, 0 );
}
#endif

Semaphore::~Semaphore()
{
#ifdef __APPLE__
  sem_unlink( fName.c_str() );
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
