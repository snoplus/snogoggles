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
{
    stringstream configFileName;                                                                                                                                                                                                      
    configFileName << getenv( "VIEWERROOT" ) << "/data/geodesic.xml";
    Configuration config = Configuration( configFileName.str(), false );
    std::vector< ConfigurationTable* >::iterator itr;
    itr = config.GetTableBegin();
    fOutlineVBO.Load( *itr );
    itr++;
    fFullVBO.Load( *itr );
}

void GeodesicSphere::Render() const
{
    glEnable( GL_DEPTH_TEST );
    glColorMask( GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE );
    fFullVBO.Render( GL_TRIANGLES );
    glColorMask( GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE );
    fOutlineVBO.Render( GL_LINES );
    glDisable( GL_DEPTH_TEST );
    glClear( GL_DEPTH_BUFFER_BIT );
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
