////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Polyhedrons3d
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


#ifndef __Viewer_Frames_Polyhedrons3d__
#define __Viewer_Frames_Polyhedrons3d__

#include <Viewer/GeoManager3d.hh>
#include <Viewer/Polyhedron.hh>
#include <vector>
#include <string>

namespace Viewer {
namespace Frames {

class Polyhedrons3d : public GeoManager3d {

public:

    Polyhedrons3d() { }

    virtual ~Polyhedrons3d() { }

    virtual std::string GetFilename() = 0;

    /// Creates all the GUI objects for the module.
    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea ) { }

    void LoadFile( );

    /// Loads configuration
    virtual void LoadConfiguration( ConfigurationTable* configTable ) { }

    /// Saves configuration
    virtual void SaveConfiguration( ConfigurationTable* configTable ) { }

    /// Event loop for the camera manager.
    virtual void EventLoop( const GUIReturn& g ) { }

    /// Renders the geometry.
    void RenderGeometry( );

private:

    std::vector< Polyhedron > fPolyhedrons;

}; // class Polyhedrons3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_Polyhedrons3d__
