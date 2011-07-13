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
///     08/07/11 : Olivia Wasalski - Slight refactoring of the static private members. \n
///     12/07/11 : Olivia Wasalski - Added the SuggestedAxisLength method. \n
///     13/07/11 : Olivia Wasalski - Changed the TVector3 objects to Vector3 objects. \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Arcball3d__
#define __Viewer_Frames_Arcball3d__

#include <Viewer/CameraManager3d.hh>
#include <Viewer/GUIReturn.hh>
#include <Viewer/Vector3.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer {

    class ConfigurationTable;
    class GUIManager;

    namespace GUIs {
        class SpriteButton;
    }; // namepsace GUIs

namespace Frames {

class Arcball3d : public CameraManager3d {

public:

    Arcball3d();

    ~Arcball3d() { }

    static std::string Name() { return "Arcball"; }
    virtual std::string GetName() { return Name(); }

    /// Creates all the GUI objects for the camera manager.
    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );

    /// Creates the drag area for rotating the scene.
    virtual void CreateDragArea( GUIManager& g, const sf::Rect<double>& draggableArea );

    /// Loads configuration
    virtual void LoadConfiguration( ConfigurationTable* configTable );

    /// Saves configuration
    virtual void SaveConfiguration( ConfigurationTable* configTable );

    /// Event loop for the camera manager.
    virtual void EventLoop( const GUIReturn& g );

    /// Initializes the OpenGL modelview and projection matricies.
    virtual void SetUpCameraSystem( const sf::Rect<double>& viewportRect );

    bool IsFront( const TVector3& v );

    double SuggestedAxisLength() { return 1.5 * fRadius; }

private:

    void Spin( const TVector3& axis );

    void Zoom( float speed );

    void Events( );

    // All tags for saving data to config table.
    static const std::string CAMERA_TAG;        ///< Name used to save fCamera.
    static const std::string EYE_TAG;           ///< Name used to save fEye.
    static const std::string UP_TAG;            ///< Name used to save fUp.
    static const std::string RADIUS_TAG;        ///< Name used to save fRadius.
    static const std::string CAMERA_DIST_TAG;   ///< Name used to save fCameraDist.
    static const std::string ZOOM_TAG;          ///< Name used to save fZoom.

    // All data which is saved to conig table.
    Vector3 fCamera;                    ///< Position of the camera.
    Vector3 fEye;                       ///< Point to look at.
    Vector3 fUp;                        ///< Orient the scene upwards.
    double fRadius;                     ///< Radius of the arcball.
    double fCameraDist;                 ///< Distance from the center of the camera.
    double fZoom;                       ///< Zoom factor.

    // All GUI objects.
    GUIs::SpriteButton* fSpinLeftButton;
    GUIs::SpriteButton* fSpinRightButton;
    GUIs::SpriteButton* fSpinUpButton;
    GUIs::SpriteButton* fSpinDownButton;
    GUIs::SpriteButton* fZoomInButton;
    GUIs::SpriteButton* fZoomOutButton;

    // All others.
    static const double MAX_ZOOM = 1.5; ///< Upper limit on fZoom.
    static const double MIN_ZOOM = 0.1; ///< Lower limit on fZoom.

    sf::Clock fClock;                   ///< SFML clock used to rotate the scene.

    double fSpinSpeed;                  ///< Speed of rotations.
    double fZoomSpeed;                  ///< Speed of zooming.

}; // class Arcball3d

}; // namespace Frames

}; // namespace Viewer

#endif // __Viewer_Frames_Arcball3d__
