////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Geodesic3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	12/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Geodesic3d__
#define __Viewer_Frames_Geodesic3d__

#include <Viewer/GeoManager3d.hh>
#include <string>

namespace Viewer {
    namespace GUIs {
        class CheckBoxLabel;
    };

namespace Frames {

class Geodesic3d : public GeoManager3d {

public:

    Geodesic3d();
    static std::string Name() { return "Geodesic"; }
    std::string GetName() { return Name(); }

    void LoadFile();
    void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
    virtual void LoadConfiguration( ConfigurationTable* configTable ) { }
    virtual void SaveConfiguration( ConfigurationTable* configTable ) { }
    virtual void EventLoop() { }
    void RenderGeometry();

private:
    GUIs::CheckBoxLabel* fDisplayGUI;

}; // class Geodesic3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_Geodesic3d__
