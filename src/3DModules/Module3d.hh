////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Module3d
///
/// \brief   All the modules share these capabilities.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
///     06/07/11 : Olivia Wasalski - Added the module tag. \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_Module3d__
#define __Viewer_Frames_Module3d__

#include <Viewer/GUIReturn.hh>
#include <Viewer/ConfigurationTable.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer {

    class GUIManager;

namespace Frames {

class Module3d {

public:

    virtual ~Module3d() { }

    /// Gets the name of the module instance. 
    virtual std::string GetName() = 0;
    virtual std::string GetTableName() = 0;

    static std::string NullTag() { return "NULL"; }

    /// Creates all the GUI objects for the module.
    static void CreateGUIObjectsSafe( Module3d* module, GUIManager& g, const sf::Rect<double>& optionsArea );
    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea ) = 0;

    /// Loads configuration
    static void LoadConfigurationSafe( Module3d* module, ConfigurationTable& configTable );
    virtual void LoadConfiguration( ConfigurationTable* configTable ) = 0;

    /// Saves configuration
    static void SaveConfigurationSafe( Module3d* module, ConfigurationTable& configTable );
    virtual void SaveConfiguration( ConfigurationTable* configTable ) = 0;

    /// Event loop for the camera manager.
    static void EventLoopSafe( Module3d* module );
    virtual void EventLoop( ) = 0;

    static const std::string MODULE_TAG;

}; // class Module3d

}; // namespace Frames

}; // namespace Viewer

#endif // __Viewer_Frames_Module3d__
