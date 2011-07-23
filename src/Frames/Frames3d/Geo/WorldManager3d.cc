#include <Viewer/World.hh>
#include <Viewer/VisMap.hh>
#include <Viewer/WorldManager3d.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ConfigurationTable.hh>

namespace Viewer {
namespace Frames {

WorldManager3d::WorldManager3d() 
{
    fGeoRenderType = SOLID;
}

WorldManager3d::~WorldManager3d() 
{
    delete fWorld;      fWorld = NULL;
    delete fVisMap;     fVisMap = NULL;
}

void WorldManager3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    // TODO:
}

void WorldManager3d::SetWorld( World* world )
{
    fWorld = world;
    if( fVisMap != NULL )
        fWorld->SetVisMap( *fVisMap );
}

void WorldManager3d::LoadConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::GetEnumSafe< GeoRenderType >( configTable, "geoRenderType", fGeoRenderType );
    fVisMap->LoadSafeFromParentTable( configTable, "visMap" );
}

void WorldManager3d::SaveConfiguration( ConfigurationTable* configTable )
{
    configTable->SetI( "geoRenderType", fGeoRenderType );
    fWorld->GetVisMap().SaveToParentTable( configTable, "visMap" );
}

void WorldManager3d::EventLoop( )
{
    // TODO:
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
            RenderOutline();
            break;
    }
}

void WorldManager3d::RenderOutline( )
{
    glClear(GL_STENCIL_BUFFER_BIT);

    glEnable(GL_STENCIL_TEST);
    glDisable(GL_DEPTH_TEST);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    glStencilFunc(GL_ALWAYS, 1, 0xFFFF );
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);
    RenderPolygonMode( GL_FILL );

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    glStencilFunc(GL_NOTEQUAL, 1, 0xFFFF );
    glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

    glLineWidth (3.0f);
    RenderPolygonMode( GL_LINE );
    glLineWidth (1.0f);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
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
