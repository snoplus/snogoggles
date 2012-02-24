#include <Viewer/World.hh>
#include <Viewer/VisMap.hh>
#include <Viewer/WorldManager3d.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/RadioCheckBoxes.hh>

namespace Viewer {
namespace Frames {

WorldManager3d::WorldManager3d() 
{
    fGeoRenderType = WIREFRAME;
    fWorld = NULL;
}

WorldManager3d::~WorldManager3d() 
{
    if( fWorld != NULL )
    {
        delete fWorld;
        fWorld = NULL;
    }
}

void WorldManager3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    std::vector< std::string > names = fWorld->GetVisMap().GetNames();
    double shift = optionsArea.Height / ( names.size() + 4 );
    sf::Rect< double > rect( optionsArea.Left, optionsArea.Top, optionsArea.Width, optionsArea.Width/5 );
    for( int i = 0; i < names.size(); i++ )
    {
        fGUIs[ names.at(i) ] = g.NewGUI< GUIs::CheckBoxLabel >( rect );
        fGUIs[ names.at(i) ]->SetLabel( names.at(i) );
        fGUIs[ names.at(i) ]->SetState( fWorld->GetVisMap().IsVisible( names.at(i) ) );
        rect.Top += shift;
    }

    std::vector< std::string > labels;
    labels.push_back( "Solid" );
    labels.push_back( "Wireframe" );
    labels.push_back( "Outline" );

    rect.Height = 3 * rect.Height;
    fRenderTypeGUI = g.NewGUI< GUIs::RadioCheckBoxes >( rect );
    fRenderTypeGUI->Initialise( labels );
    //fRenderTypeGUI->SetState( fGeoRenderType );
}

void WorldManager3d::SetWorld( World* world )
{
    fWorld = world;
    if( fVisMap.IsEmpty() == false )
        fWorld->SetVisMap( fVisMap );
}

void WorldManager3d::LoadConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::GetEnumSafe< GeoRenderType >( configTable, "geoRenderType", fGeoRenderType );
    fVisMap.LoadSafeFromParentTable( configTable, "visMap" );
}

void WorldManager3d::SaveConfiguration( ConfigurationTable* configTable )
{
    configTable->SetI( "geoRenderType", fGeoRenderType );
    fWorld->GetVisMap().SaveToParentTable( configTable, "visMap" );
}

void WorldManager3d::EventLoop( )
{
    std::map< std::string, GUIs::CheckBoxLabel* >::iterator itr;
    if( fGUIs.empty() == false )
        for( itr = fGUIs.begin(); itr != fGUIs.end(); itr++ )
            fWorld->SetVisibility( itr->first, itr->second->GetState() );

    if( fRenderTypeGUI != NULL )
        fGeoRenderType = fRenderTypeGUI->GetEnumState< GeoRenderType >();
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
