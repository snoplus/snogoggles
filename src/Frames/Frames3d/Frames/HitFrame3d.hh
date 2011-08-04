////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HitFrame3d
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

#ifndef __Viewer_Frames_HitFrame3d__
#define __Viewer_Frames_HitFrame3d__

#include <iostream>

#include <Viewer/BaseFrame3d.hh>

namespace Viewer {
namespace Frames {
	class ModuleManager3d;

class HitFrame3d : public BaseFrame3d {
public:
	static inline std::string Name();
	inline std::string GetName();
	ModuleManager3d* CreateModuleManager();
	inline sf::Rect< double > GetViewportArea();
	void CreateGUIObjects();

}; // class HitFrame3d

////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////
std::string HitFrame3d::Name()
{
	return "Hits";
}

std::string HitFrame3d::GetName()
{
	return Name();
}

sf::Rect< double > HitFrame3d::GetViewportArea()
{
	return sf::Rect< double >( 0, 0, 0.88, 0.88 );
}

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_HitFrame3d__
