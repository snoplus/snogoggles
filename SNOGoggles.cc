////////////////////////////////////////////////////////////////////////
/// \file SNOGoggles
///
/// \brief   Entry point to SNOGoggles viewer
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  The main function is defined here.
///
////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

#include <Viewer/ViewerWindow.hh>
#include <Viewer/Semaphore.hh>
#include <Viewer/LoadRootFileThread.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

int main( int argc, char *argv[] )
{
  XMLPlatformUtils::Initialize();

  ViewerWindow& viewer = ViewerWindow::GetInstance();

  viewer.Initialise();
  LoadRootFileThread* loadData;
  { // Scoping to protect semaphore from runtime errors and seg faults
    Semaphore sema;
    if( argc < 2 )
      {
	cout << "Wrong number of arguments, try snogoggles File.root" << endl;
	return 1;
      }
    loadData = new LoadRootFileThread( argv[1], sema );
    // Wait for first event to be loaded
    sema.Wait();
  }

  viewer.Run();
  viewer.Destruct();

  loadData->KillAndWait();

  delete loadData;
  XMLPlatformUtils::Terminate();
  return 0;
}
