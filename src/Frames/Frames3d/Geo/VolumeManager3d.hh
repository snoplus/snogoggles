////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::VolumeManager3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	19/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_VolumeManager3d__
#define __Viewer_Frames_VolumeManager3d__

#include <Viewer/GeoManager3d.hh>
#include <string>

namespace Viewer {

    class Volume;

namespace Frames {

class VolumeManager3d : public GeoManager3d {

public:

    VolumeManager3d() { }

    virtual ~VolumeManager3d() { }

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
    virtual void RenderGeometry( );

    virtual Volume* GetVolume() = 0;

protected:

    void RenderWireframe();

    Volume* fVolume;

}; // class VolumeManager3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_VolumeManager3d__
