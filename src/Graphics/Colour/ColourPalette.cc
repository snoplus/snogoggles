#include <sstream>
#include <stdlib.h>
using namespace std;

#include <Viewer/ColourPalette.hh>
#include <Viewer/ConfigurationFile.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

ColourPalette::ColourPalette()
{
  Load( "default" );
}

void 
ColourPalette::Load( const std::string& fileName )
{
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/gui/colour/" << fileName << ".xml";
  ConfigurationFile loadConfig( configFileName.str(), false );
  if( loadConfig.GetVersion() != 1 )
    throw ConfigurationFile::NoFileError( "Configuration version miss match" );
  const ConfigurationTable* rootTable = loadConfig.GetTable();
  const ConfigurationTable* primaryTable = rootTable->GetTable( "PrimaryColours" );
  for( unsigned int uColour = 0; uColour <= 9; uColour++ )
    {
      stringstream tableName;
      tableName << "colour" << uColour;
      fPrimaryColours[(EColour)uColour] = Colour( primaryTable->GetTable( tableName.str() ) );
    }
  const ConfigurationTable* stopTable = rootTable->GetTable( "ColourStops" );
  fColourStops.clear();
  for( unsigned int uStop = 0; uStop < stopTable->GetNumTables(); uStop++ )
    {
      stringstream tableName;
      tableName << "stop" << uStop;
      const ConfigurationTable* configTable = stopTable->GetTable( tableName.str() );
      fColourStops.push_back( pair< double, Colour >( configTable->GetD( "value" ), Colour( configTable ) ) );
    }
}

Colour
ColourPalette::GetColour( double value ) const
{
  unsigned int uStop = 0;
  for( uStop = 1; uStop < fColourStops.size() - 1; uStop++ )
    if( fColourStops[uStop].first > value )
      break;
  const double regionFraction = ( value - fColourStops[uStop - 1].first ) / ( fColourStops[uStop].first - fColourStops[uStop - 1].first );
  Colour result = fColourStops[uStop - 1].second;
  result.AddColourFraction( fColourStops[uStop].second, regionFraction );
  return result;
}
