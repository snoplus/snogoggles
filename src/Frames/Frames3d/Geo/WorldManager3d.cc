#include <Viewer/World.hh>
#include <Viewer/WorldManager3d.hh>
#include <Viewer/VisAttributes.hh>
#include <iostream>

namespace Viewer {
namespace Frames {

WorldManager3d::WorldManager3d() 
{
    fGeoRenderType = WIREFRAME;
}

WorldManager3d::~WorldManager3d() 
{
    delete fWorld;
    fWorld = NULL;
}

void WorldManager3d::LoadFile()
{
    fWorld = GetWorld();
}

void WorldManager3d::RenderGeometry()
{
    switch( fGeoRenderType )
    {
        case SOLID:
            RenderPolygonMode( GL_FILL );
            break;
        case WIREFRAME:
            RenderPolygonMode( GL_LINE );
            break;
        case OUTLINE:
            break;
    }
}

void WorldManager3d::RenderPolygonMode( GLenum e )
{
    glPolygonMode( GL_FRONT_AND_BACK, e );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );

    fWorld->Render();

    glDisable( GL_CULL_FACE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

}; // namespace Frames
}; // namespace Viewer
