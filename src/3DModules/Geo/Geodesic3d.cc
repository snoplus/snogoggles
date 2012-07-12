#include <Viewer/Geodesic3d.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/GeodesicSphere.hh>

namespace Viewer {
namespace Frames {

Geodesic3d::Geodesic3d() 
{
    fDisplayGUI = NULL;
}

void Geodesic3d::LoadFile()
{
    GeodesicSphere::GetInstance();
}

void Geodesic3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    sf::Rect< double > rect( optionsArea );
    fDisplayGUI = g.NewGUI< GUIs::PersistLabel >( rect );
    fDisplayGUI->SetLabel( "Geodesic Geo" );
    fDisplayGUI->SetState( true );
}

void Geodesic3d::Render( const RenderState& renderState )
{
    if( fDisplayGUI->GetState() )
        GeodesicSphere::GetInstance()->Render();
}

}; // namespace Frames
}; // namespace Viewer
