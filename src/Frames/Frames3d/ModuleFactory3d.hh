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
///     05/07/11 : Olivia Wasalski - Now is a singleton class. Also
///                stores default module names as strings. Finally,
///                creates modules from the config table. \n
///
/// \detail 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ModuleFactory3d__
#define __Viewer_Frames_ModuleFactory3d__

#include <Viewer/ConfigurationTable.hh>

#include <vector>
#include <string>

namespace Viewer {
namespace Frames {

    class Manager3d;

class ModuleFactory3d {

public:

    static ModuleFactory3d* GetInstance( );

    void SetAllModules( Manager3d* manager3d, std::vector<std::string>& modules );

    void SetAllModuleTypes( Manager3d* manager3d, ConfigurationTable& configTable );

    inline std::string GetDefaultCameraManager() { return fDefaultCameraManager; }

private:

    std::string GetModuleType( ConfigurationTable& configTable, const std::string& tableName, const std::string& defaultName );

    static ModuleFactory3d* fInstance;

    ModuleFactory3d( );

    std::string fDefaultCameraManager;
    std::string fDefaultHitManager;
    std::string fDefaultTrackManager;
    std::string fDefaultGeoManager;
    std::string fDefaultFitterManager;


}; // class ModuleFactory

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_ModuleFactory3d__
