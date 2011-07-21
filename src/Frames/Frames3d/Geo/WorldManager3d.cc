#include <Viewer/World.hh>
#include <Viewer/WorldManager3d.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/GeoTranslator.hh>

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

void WorldManager3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    // TODO:
}

void WorldManager3d::LoadFile()
{
    fWorld = GetWorld();
    if( fMap.empty() == false )
        fWorld->SetVisAttributeMap( fMap );
}

void WorldManager3d::LoadConfiguration( ConfigurationTable* configTable )
{
    LoadVisAttributes( configTable );
}

void WorldManager3d::SaveConfiguration( ConfigurationTable* configTable )
{
    SaveVisAttributes( configTable );
}

void WorldManager3d::EventLoop( const GUIReturn& g )
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
            // TODO:
            break;
    }
}

void WorldManager3d::LoadVisAttributes( ConfigurationTable* configTable )
{
    try { fMap = GeoTranslator::GetVisAttributeMap( configTable, "visAttributes" ); }
    catch( ConfigurationTable::NoTableError& e ) { }
}

void WorldManager3d::SaveVisAttributes( ConfigurationTable* configTable )
{
    GeoTranslator::SetVisAttributeMap( configTable, "visAttributes", fWorld->GetVisAttributeMap() );
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
