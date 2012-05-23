#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultHits3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/Axes3d.hh>

#include <Viewer/ModuleManager3d.hh>
#include <Viewer/ModuleManagerFactory3d.hh>
#include <Viewer/HitFrame3d.hh>

namespace Viewer {
namespace Frames {

ModuleManager3d* HitFrame3d::CreateModuleManager()
{
	return ModuleManagerFactory3d::GetInstance()->New(
		Arcball3d::Name(),
		DefaultHits3d::Name(),
		"NULL",
		Geodesic3d::Name(),
		"NULL"
	);
}

void HitFrame3d::CreateGUIObjects()
{
    fModuleManager->fCameraManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0 , 0.88 , 0.48 , 0.08 ) );
    fModuleManager->fCameraManager->CreateDragArea( fGUIManager, sf::Rect<double>( 0, 0, 1, 0.88 ) );
	fModuleManager->fAxes->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0, 0.96, 0.23, 0.04 ) );
    fModuleManager->fGeoManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.25, 0.96, 0.23, 0.04 ) );
    fModuleManager->fHitManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0.5 , 0.96 , 0.5 , 0.04 ) );
}

}; // namespace Frames
}; // namespace Viewer
