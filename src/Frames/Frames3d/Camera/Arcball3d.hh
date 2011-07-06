////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Arcball3d
///
/// \brief   Arcball which is responsible for managing 
///	     the OpenGL modelview and projection matricies.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	06/07/11 : Olivia Wasalski - New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Arcball3d__
#define __Viewer_Frames_Arcball3d__

#include <Viewer/CameraManager3d.hh>
#include <SFML/Graphics.hpp>
#include <TVector3.h>
#include <string>

namespace Viewer {
namespace Frames {

class Arcball3d : public CameraManager3d {

public:

    Arcball3d();

    ~Arcball3d() { }

    static std::string Name() { return "arcball"; }
    virtual std::string GetName() { return Name(); }

    /// Creates all the GUI objects for the camera manager.
    virtual void CreateGUIObjects( GUIManager* g, const sf::Rect<double>& optionsArea );

    /// Creates the drag area for rotating the scene.
    virtual void CreateDragArea( GUIManager* g, const sf::Rect<double>& draggableArea );

    /// Loads configuration
    virtual void LoadConfiguration( ConfigurationTable* configTable );

    /// Saves configuration
    virtual void SaveConfiguration( ConfigurationTable* configTable );

    /// Event loop for the camera manager.
    virtual void EventLoop( const GUIReturn& g );

    /// Initializes the OpenGL modelview and projection matricies.
    virtual void SetUpCameraSystem( const sf::Rect<double>& viewportRect );

    bool IsFront( TVector3 v );

private:

    static std::string CameraTag() { return "camera"; }             ///< Name used to save fCamera.
    static std::string EyeTag() { return "eye"; }                   ///< Name used to save fEye.
    static std::string UpTag() { return "up"; }                     ///< Name used to save fUp.

    static std::string RadiusTag() { return "radius"; }             ///< Name used to save fRadius.
    static std::string CameraDistTag() { return "cameraDist"; }     ///< Name used to save fCameraDist.
    static std::string ZoomTag() { return "zoom"; }                 ///< Name used to save fZoom.

    TVector3 fCamera;                   ///< Position of the camera.
    TVector3 fEye;                      ///< Point to look at.
    TVector3 fUp;                       ///< Orient the scene upwards.

    double fRadius;                     ///< Radius of the arcball.
    double fCameraDist;                 ///< Distance from the center of the camera.
    double fZoom;                       ///< Zoom factor.

    static const double MAX_ZOOM = 1.5; ///< Upper limit on fZoom.
    static const double MIN_ZOOM = 0.5; ///< Lower limit on fZoom.

    sf::Clock fClock;                   ///< SFML clock used to rotate the scene.


}; // class Arcball3d

}; // namespace Frames

}; // namespace Viewer

#endif // __Viewer_Frames_Arcball3d__
