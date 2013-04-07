////////////////////////////////////////////////////////////////////////
/// \class Viewer::Camera3d
///
/// \brief   The base class for all 3d cameras
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original Camera3d class to take account
///          of codebase changes.
///          The camera manager is responsible for: \n
///
///     Initializing the projection matrix for OpenGL. \n
///     Initializing the model-view matrix for OpenGL. \n
///     All scene wide transformations and rotations. \n
///     Returning a boolean value which represents whether
///     a specified vector is in the front or back half of
///     the detector. \n
///     Creating GUI objects to manage the camera.\n
///     Appropriately responding when passed Viewer::Events. \n
///     Drawing a blank screen at the zero line to act as a
///     filter for objects in the back half of the detector. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Camera3d__
#define __Viewer_Camera3d__

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/Module3d.hh>

namespace Viewer
{

class Camera3d : public Module3d
{
public:
  Camera3d( RectPtr rect ) : Module3d( rect ) { }
  virtual ~Camera3d() { };
  /// Set up the openGL camera and viewport
  virtual void SetGLCamera() = 0;
};

} //::Viewer

#endif
