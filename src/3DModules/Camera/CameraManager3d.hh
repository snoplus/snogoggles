////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::CameraManager3d
///
/// \brief   Abstract class which is responsible for managing 
///	     the OpenGL modelview and projection matricies.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
/// 	05/07/11 : Olivia Wasalski - Added the SuggestedAxisLength method. \n
///     05/21/12 : Olivia Wasalski - Added render screen method to differentiate between 
///                                  front and back objects. \n
///
/// \details 	The camera manager is responsible for: \n
///
///		Initializing the projection matrix for OpenGL. \n
///		Initializing the model-view matrix for OpenGL. \n
///		All scene wide transformations and rotations. \n
///		Returning a boolean value which represents whether 
///		a specified vector is in the front or back half of 
///		the detector. \n
///		Creating GUI objects to manage the camera.\n
///		Appropriately responding when passed Viewer::Events. \n
///
///		To create GUI objects, the camera manager needs both 
///		the area for the camera manager's GUI objects and an 
///		additional area for dragging. The drag area occupies 
///		the same area on the screen as the viewport for the 
///		3d display. The camera manager is the only module 
///		which may not be specified to "null".
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_CameraManager3d__
#define __Viewer_Frames_CameraManager3d__

#include <Viewer/Module3d.hh>
#include <SFML/Graphics.hpp>
#include <string>

namespace Viewer {

namespace Frames {

class CameraManager3d : public Module3d {

public:

    virtual ~CameraManager3d() { }

    static std::string TableName() { return "CameraManager3d"; }
    std::string GetTableName() { return TableName(); }

    /// Creates all the GUI objects for the camera manager.
    virtual void CreateDragArea( GUIManager& g, const sf::Rect<double>& draggableArea ) = 0;

    /// Initializes the OpenGL modelview and projection matricies.
    virtual void SetUpCameraSystem( const sf::Rect<double>& viewportRect ) = 0;
    virtual void RenderScreen() = 0;

    virtual double SuggestedAxisLength() = 0;

}; // class CameraManager3d

}; // namespace Frames

}; // namespace Viewer

#endif // __Viewer_Frames_CameraManager3d__
