#include <sstream>
using namespace std;

#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationFile.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

GUIProperties::GUIProperties()
{
  fChanged = true;
}

GUIProperties::~GUIProperties()
{

}

void
GUIProperties::Destruct()
{
  delete fGUIConfiguration;
}

void 
GUIProperties::PreInitialise( const ConfigurationTable* config )
{
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/gui/";
  if( config != NULL && config->Has( "guiConfig" ) )
    configFileName << config->GetS( "guiConfig" );
  else
    configFileName << "default.xml";  
  fGUIConfiguration = new ConfigurationFile( configFileName.str(), false );
}

void
GUIProperties::TextureInitialise()
{
  fGUITextures.Initialise();
}

const ConfigurationTable*
GUIProperties::GetConfiguration( const std::string& object ) const
{
  return fGUIConfiguration->GetTable()->GetTable( object );
}

unsigned int
GUIProperties::GetNumDesktops() const
{
  return fGUIConfiguration->GetTable()->GetI( "desktops" );
}
