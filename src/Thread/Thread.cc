#include <Viewer/Thread.hh>
using namespace Viewer;

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
  threadInstance->RunT();
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
Thread::RunT()
{
  while( fRun )
    Run();
  pthread_exit(NULL);
}

void
Thread::Run()
{

}
