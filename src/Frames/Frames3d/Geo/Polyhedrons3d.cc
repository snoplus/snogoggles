#include <Viewer/Polyhedrons3d.hh>
#include <Viewer/Polyhedron.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <string>
#include <iostream>
#include <sstream>

namespace Viewer {
namespace Frames {

void Polyhedrons3d::LoadFile()
{
/*
    Configuration config = Configuration( GetFilename(), false );

    std::vector< ConfigurationTable* >::iterator itr;
    for( itr = config.GetTableBegin(); itr != config.GetTableEnd(); itr++ )
        fPolyhedrons.push_back( ConfigTableUtils::GetPolyhedron( *itr ) );


    Configuration outConfig = Configuration( "data/geodesic2.xml", true );
    for( int i = 0; i < fPolyhedrons.size(); i++ )
        ConfigTableUtils::SetPolyhedron( outConfig.NewTable( "polyhedron" ), fPolyhedrons.at(i) );

    outConfig.SaveConfiguration();
*/
}

void Polyhedrons3d::RenderGeometry( )
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );

    for( int i = 0; i < fPolyhedrons.size(); i++ )
        fPolyhedrons.at(i).RenderOpenGL();

    glDisable( GL_CULL_FACE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

}; // namespace Frames
}; // namespace Viewer
