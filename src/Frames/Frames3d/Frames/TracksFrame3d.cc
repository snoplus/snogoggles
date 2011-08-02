#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/TracksFrame3d.hh>

namespace Viewer {
namespace Frames {

TracksFrame3d::TracksFrame3d()
    : Specialized3d( Arcball3d::Name() + " NULL " + DefaultTracks3d::Name() + " " + Geodesic3d::Name() ) { }

void TracksFrame3d::CreateGUIObjects()
{
    fCameraManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0 , 0.92 , 0.48 , 0.08 ) );
    CreateAxesGUIObject( sf::Rect< double >( 0.48, 0.94, 0.23, 0.04 ) );
    fGeoManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.74, 0.94, 0.23, 0.04 ) );
    fTrackManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0.8 , 0 , 0.2 , 0.92 ) );
}

}; // namespace Frames
}; // namespace Viewer
