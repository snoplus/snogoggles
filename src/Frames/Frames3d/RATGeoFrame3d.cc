#include <Viewer/Arcball3d.hh>
#include <Viewer/RATGeo3d.hh>
#include <Viewer/Axes3d.hh>

#include <Viewer/ModuleManager3d.hh>
#include <Viewer/ModuleManagerFactory3d.hh>
#include <Viewer/RATGeoFrame3d.hh>

namespace Viewer {
namespace Frames {

ModuleManager3d* RATGeoFrame3d::CreateModuleManager()
{
	return ModuleManagerFactory3d::GetInstance()->New(
		Arcball3d::Name(),
		"NULL",
		"NULL",
		RATGeo3d::Name(),
		"NULL"
	);
}

void RATGeoFrame3d::CreateGUIObjects()
{
    fModuleManager->fCameraManager->CreateGUIObjects( fGUIManager, sf::Rect<double>( 0 , 0.92 , 0.5 , 0.08 ) );
	fModuleManager->fAxes->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.5, 0.94, 0.23, 0.04 ) );
	fModuleManager->fGeoManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0.8, 0, 0.2, 1 ) );

}

}; // namespace Frames
}; // namespace Viewer
