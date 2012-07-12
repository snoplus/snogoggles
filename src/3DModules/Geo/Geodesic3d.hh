////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Geodesic3d
///
/// \brief  Geometry manager implementation that renders a geodesic sphere.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	12/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details Geo manager module implementation that renders a geodesic
///          sphere. Utilizes the GeodesicSphere singleton to store the 
///          VBOs necessary. A single GUI check box to enable or disable
///          rendering the geometry. Standard geometry. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Geodesic3d__
#define __Viewer_Frames_Geodesic3d__

#include <Viewer/GeoManager3d.hh>
#include <string>

namespace Viewer {
    namespace GUIs {
        class PersistLabel;
    };

namespace Frames {

class Geodesic3d : public GeoManager3d {

public:

    Geodesic3d();
    static std::string Name() { return "Geodesic"; }
    std::string GetName() { return Name(); }

    void LoadFile();
    void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
    virtual void LoadConfiguration( const ConfigurationTable* configTable ) { }
    virtual void SaveConfiguration( ConfigurationTable* configTable ) { }
    virtual void EventLoop() { }
    void Render( const RenderState& renderState );

private:
    GUIs::PersistLabel* fDisplayGUI;

}; // class Geodesic3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_Geodesic3d__
