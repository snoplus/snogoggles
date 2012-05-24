#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/Axes3d.hh>

#include <Viewer/ModuleManager3d.hh>
#include <Viewer/ModuleManagerFactory3d.hh>
#include <Viewer/TrackFrame3d.hh>

namespace Viewer {
namespace Frames {

ModuleManager3d* TrackFrame3d::CreateModuleManager()
{
	return ModuleManagerFactory3d::GetInstance()->New(
		Arcball3d::Name(),
		"NULL",
		DefaultTracks3d::Name(),
		Geodesic3d::Name(),
		"NULL"
	);
}

void TrackFrame3d::CreateGUIObjects()
{
    fModuleManager->fCameraManager->CreateDragArea( fGUIManager, sf::Rect<double>( 0 , 0 , 0.8 , 0.8 ) );
	fModuleManager->fAxes->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.5, 0.94, 0.23, 0.04 ) );
	fModuleManager->fGeoManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.75, 0.94, 0.23, 0.04 ) );
	fModuleManager->fTrackManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.8, 0, 0.2, 0.92 ) );

}

}; // namespace Frames
}; // namespace Viewer
