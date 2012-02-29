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
#include <string>
using namespace std;

#include <Viewer/ViewerWindow.hh>
#include <Viewer/Semaphore.hh>
#include <Viewer/LoadRootFileThread.hh>
#include <Viewer/ReceiverThread.hh>

#include <Viewer/GeodesicSphere.hh>
#include <Viewer/EventData.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

void Initialise();

int main( int argc, char *argv[] )
{
  XMLPlatformUtils::Initialize();

  ViewerWindow& viewer = ViewerWindow::GetInstance();

  viewer.Initialise();

  Thread* loadData;
  if( string( argv[1] ) == string( "-s" ) || string( argv[1] ) == string( "-p" ) ) // Temp horrible way...
    {
      { // Scoping to protect semaphore from runtime errors and seg faults
	Semaphore sema;
	if( argc < 3 )
	  {
	    cout << "Wrong number of arguments, try snogoggles -s tcp://localhost:5024" << endl;
	    return 1;
	  }
	if( string( argv[1] ) == string( "-p" ) )
	  loadData = new ReceiverThread( argv[2], sema, false );
	else
	  loadData = new ReceiverThread( argv[2], sema, true );
	// Wait for first event to be loaded
	sema.Wait();
      }
    }
  else
    {
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
    }

  Initialise();
  viewer.Run();
  viewer.Destruct();

  loadData->KillAndWait();

  delete loadData;
  XMLPlatformUtils::Terminate();
  return 0;
}

void Initialise()
{
  GeodesicSphere::GetInstance(); // Forces it to load, should be initialised, PHIL
  EventData::GetInstance().Initialise();
}
