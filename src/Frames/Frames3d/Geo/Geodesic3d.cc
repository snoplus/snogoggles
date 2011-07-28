#include <Viewer/Geodesic3d.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/XMLLoader3d.hh>
#include <Viewer/WorldManager3d.hh>

namespace Viewer {
namespace Frames {

Geodesic3d::Geodesic3d() 
    : WorldBase3d( new XMLLoader3d( "geodesic.xml" ), new WorldManager3d ) 
{
    fDisplayGUI = NULL;
}

void Geodesic3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    sf::Rect< double > rect( optionsArea );
    fDisplayGUI = g.NewGUI< GUIs::CheckBoxLabel >( rect );
    fDisplayGUI->SetLabel( "Geodesic Geo" );
    fDisplayGUI->SetState( true );
}

void Geodesic3d::RenderGeometry()
{
    if( fDisplayGUI != NULL )
    {
        if( fDisplayGUI->GetState() == true )
            fManager->RenderPolygonMode( GL_LINE );
    }
    else
        fManager->RenderPolygonMode( GL_LINE );
}

}; // namespace Frames
}; // namespace Viewer
