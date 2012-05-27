#include <cstddef>
#include <stdlib.h>
#include <sstream>
using namespace std;

#include <Viewer/ConfigurationFile.hh>
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
{
    stringstream configFileName;
    configFileName << getenv( "VIEWERROOT" ) << "/data/geodesic.xml";
    ConfigurationFile config( configFileName.str(), false );
    const ConfigurationTable* configTable = config.GetTable();
    fOutlineVBO.Load( configTable->GetTable(0) );
    fFullVBO.Load( configTable->GetTable(1) );
}

void GeodesicSphere::Render() const
{
    glEnable( GL_DEPTH_TEST );
    glColorMask( GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE );
    fFullVBO.Render( GL_TRIANGLES );
    glColorMask( GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE );
    fOutlineVBO.Render( GL_LINES );
    glDisable( GL_DEPTH_TEST );
}

const Polyhedron& GeodesicSphere::GetPolyhedron()
{
    return *fPolyhedron;
}

const Colour GeodesicSphere::GetColour()
{
    return ColourPalette::gPalette->GetPrimaryColour( eGrey );
}

}; // namespace Viewer
