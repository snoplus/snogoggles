#include <cstddef>
#include <stdlib.h>
#include <sstream>
using namespace std;

#include <Viewer/Configuration.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/SerializableFactory.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/GeodesicSphere.hh>

namespace Viewer {

GeodesicSphere* GeodesicSphere::fInstance = NULL;

GeodesicSphere* GeodesicSphere::GetInstance()
{
	if( fInstance == NULL )
		fInstance = new GeodesicSphere();

	return fInstance;
}

GeodesicSphere::GeodesicSphere()
	: fColour( ColourPalette::gPalette->GetPrimaryColour( eGrey ) )
{
  stringstream configFileName;                                                                                                                                                                                                           
  configFileName << getenv( "VIEWERROOT" ) << "/data/geodesic.xml";
  Configuration config = Configuration( configFileName.str(), false );
  std::vector< ConfigurationTable* >::iterator itr;
  itr = config.GetTableBegin();
  ConfigurationTable* volumeTable = (*itr)->GetTable( "volume" );
  fPolyhedron = SerializableFactory::GetInstance()->NewPtr< Polyhedron >( volumeTable, "polyhedron" );
}

const Polyhedron& GeodesicSphere::GetPolyhedron()
{
	return *fPolyhedron;
}

const Colour& GeodesicSphere::GetColour()
{
	return fColour;
}

}; // namespace Viewer
