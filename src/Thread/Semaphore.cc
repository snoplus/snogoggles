#ifdef __APPLE__
#include <sstream>
using namespace std;
#endif

#include <Viewer/Semaphore.hh>
using namespace Viewer;

Semaphore::Semaphore()
{
#ifdef __APPLE__
  stringstream name;
  fID = fsNumSemaphores++;
  name << "Sema" << fID;
  fSemaphore = sem_open( name.str().c_str(), O_CREAT | O_EXCL, 0644, 0 );
#else
  sem_init( &fSemaphore, 0, 0 );
#endif
}

Semaphore::~Semaphore()
{
#ifdef __APPLE__
  stringstream name;
  name << "Sema" << fID;
  sem_unlink( name.str().c_str() );
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
