#include <sstream>
using namespace std;

#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationFile.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

GUIProperties::GUIProperties()
{
  
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

/*sf::Rect<double>
GUIProperties::GetFrameArea() const
{
  return sf::Rect<double>( fGUIConfiguration->GetTable()->GetD( "frameX" ), fGUIConfiguration->GetTable()->GetD( "frameY" ), 
                           fGUIConfiguration->GetTable()->GetD( "frameWidth" ), fGUIConfiguration->GetTable()->GetD( "frameHeight" ) );
                           }*/
