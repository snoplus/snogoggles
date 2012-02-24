////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::RATGeoFrame3d
///
/// \brief   	
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	04/08/11 : Olivia Wasalski - New File \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_RATGeoFrame3d__
#define __Viewer_Frames_RATGeoFrame3d__

#include <Viewer/BaseFrame3d.hh>

namespace Viewer {
namespace Frames {
	class ModuleManager3d;

class RATGeoFrame3d : public BaseFrame3d {
public:
  RATGeoFrame3d( RectPtr rect ) : BaseFrame3d( rect ) { }
	static inline std::string Name();
	inline std::string GetName();
	ModuleManager3d* CreateModuleManager();
	inline sf::Rect< double > GetViewportArea();
	void CreateGUIObjects();

}; // class RATGeoFrame3d

////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////
std::string RATGeoFrame3d::Name()
{
	return "RATGeometry";
}

std::string RATGeoFrame3d::GetName()
{
	return Name();
}

sf::Rect< double > RATGeoFrame3d::GetViewportArea()
{
	return sf::Rect< double >( 0, 0.05, 0.8, 0.8 );
}

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_RATGeoFrame3d__
