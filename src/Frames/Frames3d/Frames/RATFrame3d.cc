#include <Viewer/Arcball3d.hh>
#include <Viewer/RATGeo3d.hh>
#include <Viewer/RATFrame3d.hh>

namespace Viewer {
namespace Frames {

RATFrame3d::RATFrame3d()
    : Specialized3d( Arcball3d::Name() + " NULL NULL " + RATGeo3d::Name() ) { }

void RATFrame3d::CreateGUIObjects()
{
    fCameraManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0, 0.92, 0.48, 0.08 ) );
    fGeoManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.8, 0, 0.2, 1 ) );
}

}; // namespace Frames
}; // namespace Viewer
