////////////////////////////////////////////////////////////////////////
/// \class Viewer::Semaphore
///
/// \brief   Semaphore class
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     04/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Semaphore, syncronisation between threads.
///
////////////////////////////////////////////////////////////////////////


#ifndef Semaphore_hh
#define Semaphore_hh

#include <semaphore.h>

namespace Viewer
{

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
  sem_t* fSemaphore; // Must be named on a Mac
  static unsigned int fsNumSemaphores;
  unsigned int fID;
#else
  sem_t fSemaphore;
#endif
};

} // ::Viewer

#endif
