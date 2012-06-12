#include <sstream>
using namespace std;

#include <Viewer/GUIColourPalette.hh>
#include <Viewer/ConfigurationFile.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

GUIColourPalette::GUIColourPalette()
{
  fInverted = false;
  Load( "gui-default.xml" );
}

GUIColourPalette::~GUIColourPalette()
{

}

Colour 
GUIColourPalette::GetBackground() const
{
  if( fInverted )
    return fInvBackground;
  else
    return fBackground;
}

Colour
GUIColourPalette::GetText() const
{
  if( fInverted )
    return fInvText;
  else
    return fText;
}

void 
GUIColourPalette::Load( const std::string& fileName )
{
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/gui/colour/" << fileName;
  ConfigurationFile loadConfig( configFileName.str(), false );
  if( loadConfig.GetVersion() != 1 )
    throw ConfigurationFile::NoFileError( "Configuration version miss match" );
  const ConfigurationTable* rootTable = loadConfig.GetTable();
  {
    const ConfigurationTable* config = rootTable->GetTable( "Background" );
    fBackground = Colour( config->GetTable( "normal" ) );
    fInvBackground = Colour( config->GetTable( "inverted" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "Text" );
    fText = Colour( config->GetTable( "normal" ) );
    fInvText = Colour( config->GetTable( "inverted" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "ColourA" );
    fA[eBase] = Colour( config->GetTable( "base" ) );
    fA[eHighlight] = Colour( config->GetTable( "highlight" ) );
    fA[eActive] = Colour( config->GetTable( "active" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "ColourB" );
    fB[eBase] = Colour( config->GetTable( "base" ) );
    fB[eHighlight] = Colour( config->GetTable( "highlight" ) );
    fB[eActive] = Colour( config->GetTable( "active" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "ColourC" );
    fC[eBase] = Colour( config->GetTable( "base" ) );
    fC[eHighlight] = Colour( config->GetTable( "highlight" ) );
    fC[eActive] = Colour( config->GetTable( "active" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "ColourD" );
    fD[eBase] = Colour( config->GetTable( "base" ) );
    fD[eHighlight] = Colour( config->GetTable( "highlight" ) );
    fD[eActive] = Colour( config->GetTable( "active" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "ColourE" );
    fE[eBase] = Colour( config->GetTable( "base" ) );
    fE[eHighlight] = Colour( config->GetTable( "highlight" ) );
    fE[eActive] = Colour( config->GetTable( "active" ) );
  }
  {
    const ConfigurationTable* config = rootTable->GetTable( "ColourF" );
    fF[eBase] = Colour( config->GetTable( "base" ) );
    fF[eHighlight] = Colour( config->GetTable( "highlight" ) );
    fF[eActive] = Colour( config->GetTable( "active" ) );
  }
}


