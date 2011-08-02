#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultHits3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/HitsFrame3d.hh>

namespace Viewer {
namespace Frames {

HitsFrame3d::HitsFrame3d()
    : Specialized3d( Arcball3d::Name() + " " + DefaultHits3d::Name() + " NULL " + Geodesic3d::Name() ) { }

void HitsFrame3d::CreateGUIObjects()
{
    fCameraManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0 , 0.88 , 0.48 , 0.08 ) );
    CreateAxesGUIObject( sf::Rect< double >( 0, 0.96, 0.23, 0.04 ) );
    fGeoManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.25, 0.96, 0.23, 0.04 ) );
    fHitManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0.5 , 0.96 , 0.5 , 0.04 ) );
}

}; // namespace Frames
}; // namespace Viewer
