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
#include <fstream>
using namespace std;

#include <Viewer/ViewerWindow.hh>
#include <Viewer/Semaphore.hh>
#include <Viewer/LoadRootFileThread.hh>
#include <Viewer/ReceiverThread.hh>

#include <Viewer/RenderState.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/DataStore.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

void Initialise();
void PrintHelp();

int main( int argc, char *argv[] )
{
  // Instant help string checking
  if( argc < 2 || string( argv[1] ) == string( "-h") || string( argv[1] ) == string( "--help" ) )
    {
      PrintHelp();
      return 1;
    }

  XMLPlatformUtils::Initialize();

  ViewerWindow& viewer = ViewerWindow::GetInstance();

  viewer.PreInitialise();

  DataStore::GetInstance(); // Starts TPython on this thread

  Thread* loadData;
  if( string( argv[1] ) == string( "-s" ) ) // Temp horrible way...
    {
      Semaphore sema;
      if( argc < 3 )
        {
          PrintHelp();
          viewer.Destruct();
          return 1;
        }
      loadData = new ReceiverThread( argv[2], sema, true );
      // Wait for first event to be loaded
      sema.Wait();
    }
  else if( string( argv[1] ) == string( "-p" ) )
    {
      cout << "Not yet implmented" << endl;
    }
  else
    {
      Semaphore sema;
      ifstream test( argv[1] );
      if( test.good() == false )
        {
          PrintHelp();
          test.close();
          viewer.Destruct();
          return 1;
        }
      test.close();
      loadData = new LoadRootFileThread( argv[1], sema );
      // Wait for first event to be loaded
      sema.Wait();
    }
  Initialise();
  viewer.PostInitialise();
  viewer.Run();
  viewer.Destruct();

  loadData->KillAndWait();

  delete loadData;
  XMLPlatformUtils::Terminate();
  return 0;
}

void 
Initialise()
{
  GeodesicSphere::GetInstance(); // Forces it to load, should be initialised, PHIL
  DataStore::GetInstance().Initialise();
  RenderState::Initialise();
}

void 
PrintHelp()
{
  cout << "usage:snogoggles [options] [-p] FileName.root\n" << " or: snogoggles -s port\n";
  cout << "options:" << endl;
  cout << " -h, --help        show this help message and exit" << endl;
  cout << " -p                load packed format file" << endl;
}
