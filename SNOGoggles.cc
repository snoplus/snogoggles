////////////////////////////////////////////////////////////////////////
/// \file SNOGoggles
///
/// \brief   Entry point to SNOGoggles viewer
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     23/05/12 : P.Jones - Second Revision, New initialisation order.\n
///
/// \detail  The main function is defined here.
///
////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include <Viewer/ViewerWindow.hh>
#include <Viewer/Semaphore.hh>
#include <Viewer/LoadRootFileThread.hh>
#include <Viewer/ReceiverThread.hh>
#include <Viewer/ConfigurationFile.hh>
#include <Viewer/ConfigurationTable.hh>

#include <Viewer/RenderState.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

#include <xercesc/util/PlatformUtils.hpp>
using namespace xercesc;

const int kConfigVersion = 1; /// The configuration version expected in the xml config files.

/// Load the singletons that can be loaded without the DataStore class.
void PreInitialise();
/// Load the singletons that require event data/the DataStore class.
void PostInitialise();
/// Load the configuration, if it exists and is the correct version
ConfigurationFile* OpenConfiguration( bool output );
/// Print the help information to the terminal
void PrintHelp();

int main( int argc, char *argv[] )
{
  // Instant help string checking
  if( argc < 2 || string( argv[1] ) == string( "-h") || string( argv[1] ) == string( "--help" ) )
    {
      PrintHelp();
      return 1;
    }
  PreInitialise();
  ConfigurationFile* loadConfig = OpenConfiguration( false );
  const ConfigurationTable* loadConfigTable = NULL;
  if( loadConfig != NULL )
    loadConfigTable = loadConfig->GetTable();
  GUIProperties::GetInstance().PreInitialise( loadConfigTable );
  ViewerWindow& viewer = ViewerWindow::GetInstance();
  viewer.PreInitialise( loadConfigTable );
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
    cout << "Not yet implmented" << endl;
  else
    {
      Semaphore sema;
      ifstream test( argv[1] );
      // Check the file exists
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
  PostInitialise();
  viewer.PostInitialise( loadConfigTable );
  delete loadConfig; // No longer needed
  viewer.Run();
  ConfigurationFile* saveConfig = OpenConfiguration( true );
  viewer.SaveConfiguration( saveConfig->NewTable() );
  saveConfig->Save();
  delete saveConfig;
  viewer.Destruct();
  // Finish the thread
  loadData->KillAndWait();
  delete loadData;
  GUIProperties::GetInstance().Destruct();
  XMLPlatformUtils::Terminate();
  return 0;
}

void
PreInitialise()
{
  XMLPlatformUtils::Initialize();
  DataStore::GetInstance();
  RenderState::Initialise();
}

void 
PostInitialise()
{
  GeodesicSphere::GetInstance(); // Forces it to load, should be initialised, PHIL
  DataStore::GetInstance().Initialise();
}

void 
PrintHelp()
{
  cout << "usage:snogoggles [options] [-p] FileName.root\n" << " or: snogoggles -s port\n";
  cout << "options:" << endl;
  cout << " -h, --help        show this help message and exit" << endl;
  cout << " -p                load packed format file" << endl;
}

ConfigurationFile*
OpenConfiguration( bool output )
{
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/snogoggles.xml";
  if( output == true )
    {
      ConfigurationFile* saveConfig = new ConfigurationFile( configFileName.str(), true );
      saveConfig->SetVersion( kConfigVersion );
      return saveConfig;
    }
  else
    {
      try
        {
          ConfigurationFile* loadConfig = new ConfigurationFile( configFileName.str(), false );
          // Check file is up to date, if not throw a recoverable error (after deleting it)
          if( loadConfig->GetVersion() != kConfigVersion )
            {
              remove( configFileName.str().c_str() );
              throw ConfigurationFile::NoFileError( "Configuration version miss match" );
            }
          return loadConfig;
        }
      catch( ConfigurationFile::NoFileError& e )
        {
          cout << "No compatible configuration file found." << endl;
          return NULL;
        }
      return NULL;
    }
}
