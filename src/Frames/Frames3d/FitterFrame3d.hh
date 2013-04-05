////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::FitterFrame3d
///
/// \brief   Currently does not have any functionality - tracks have
///          not been added to the RIDS data structure.
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	04/08/11 : Olivia Wasalski - New File \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_FitterFrame3d__
#define __Viewer_Frames_FitterFrame3d__

#include <iostream>

#include <Viewer/BaseFrame3d.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer {
namespace Frames {
	class ModuleManager3d;

class FitterFrame3d : public BaseFrame3d {
public:
  FitterFrame3d( RectPtr rect ) : BaseFrame3d( rect ) { }
	static inline std::string Name();
	inline std::string GetName();
	ModuleManager3d* CreateModuleManager();
	inline sf::Rect< double > GetViewportArea();
	void CreateGUIObjects();

}; // class FitterFrame3d

////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////
std::string FitterFrame3d::Name()
{
	return "Fitters";
}

std::string FitterFrame3d::GetName()
{
	return Name();
}

sf::Rect< double > FitterFrame3d::GetViewportArea()
{
	return sf::Rect< double >( 0, 0.05, 0.8, 0.8 );
}

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_FitterFrame3d__
