////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::TrackFrame3d
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

#ifndef __Viewer_Frames_TrackFrame3d__
#define __Viewer_Frames_TrackFrame3d__

#include <iostream>

#include <Viewer/BaseFrame3d.hh>

namespace Viewer {
namespace Frames {
	class ModuleManager3d;

class TrackFrame3d : public BaseFrame3d {
public:
	static inline std::string Name();
	inline std::string GetName();
	ModuleManager3d* CreateModuleManager();
	inline sf::Rect< double > GetViewportArea();
	void CreateGUIObjects();

}; // class TrackFrame3d

////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////
std::string TrackFrame3d::Name()
{
	return "Tracks";
}

std::string TrackFrame3d::GetName()
{
	return Name();
}

sf::Rect< double > TrackFrame3d::GetViewportArea()
{
	return sf::Rect< double >( 0, 0, 0.88, 0.88 );
}

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_TrackFrame3d__
