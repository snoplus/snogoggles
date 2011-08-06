////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ModuleManagerFactory3d
///
/// \brief Singleton factory that creates a Manager3d instance
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     04/08/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ModuleManagerFactory3d__
#define __Viewer_Frames_ModuleManagerFactory3d__

#include <string>

namespace Viewer {
namespace Frames {

	class ModuleManager3d;

class ModuleManagerFactory3d {

private:
	ModuleManagerFactory3d();
public:
	static ModuleManagerFactory3d* GetInstance();
	ModuleManager3d* New( 
		const std::string& camera,
		const std::string& hits,
		const std::string& tracks,
		const std::string& geo,
		const std::string& fitter
	);
private:
	static ModuleManagerFactory3d* fInstance;

}; // class ModuleManagerFactory3d

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_ModuleManagerFactory3d__
