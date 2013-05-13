////////////////////////////////////////////////////////////////////////
/// \class Viewer::Arcball3d
///
/// \brief   The arcball camera
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original Arcball3d class to take account
///          of codebase changes.
///          Implementation of a arcball camera.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Arcball3d__
#define __Viewer_Arcball3d__

#include <TVector3.h>

#include <SFML/System/Clock.hpp>

#include <Viewer/Camera3d.hh>

namespace Viewer
{
  class Rotation;

class Arcball3d : public Camera3d
{
public:
  Arcball3d( RectPtr rect ) : Camera3d( rect ), fDragRotate( false ) { }
  virtual ~Arcball3d() { }
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process event data
  virtual void ProcessEvent( const RenderState& renderState ) { };
  /// Process run data
  virtual void ProcessRun() { };
  /// Render all 3d objects nothing to do
  virtual void Render3d() { };
  /// Set up the openGL camera and viewport
  void SetGLCamera();
  /// Return the module name
  virtual std::string GetName() { return Arcball3d::Name(); }
  static std::string Name() { return std::string( "Arcball3d" ); }
protected:
  /// Reset the rotation/zoom
  void Reset();
  /// Rotate the camera by Rotation
  void Rotate( Rotation& rotation );
  /// Rotate the camera due to the drag from start to end
  void DragRotate();

  sf::Vector2<double> fDragStartPos; /// < Drag rotate start position, in gl co-ords
  sf::Vector2<double> fDragEndPos; /// < Drag rotate end position, in gl co-ords

  bool fRotate; /// < Rotate about the z axis continuously?
  bool fDragRotate; /// < Currently dragging? Must calculate in render after camera setup
  
  TVector3 fCamera;                    ///< Position of the camera.                                                      
  TVector3 fEye;                       ///< Point to look at.
  TVector3 fUp;                        ///< Orient the scene upwards.
  double fZoom;                       ///< Zoom factor. 

  sf::Clock fClock;
};

} //::Viewer

#endif
