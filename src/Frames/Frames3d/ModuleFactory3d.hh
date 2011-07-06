////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ModuleFactory3d
///
/// \brief Singleton factory that creates all the modules
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ModuleFactory3d__
#define __Viewer_Frames_ModuleFactory3d__

#include <vector>
#include <string>

namespace Viewer {
namespace Frames {

    class Manager3d;

class ModuleFactory3d {

public:

    static void SetAllModules( Manager3d* manager3d, std::vector<std::string>& modules );


}; // class ModuleFactory

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_ModuleFactory3d__
