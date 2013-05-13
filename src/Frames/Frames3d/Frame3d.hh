////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame3d
///
/// \brief   The base class for all 3d frames
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  All 3d frames derive from this, adds the standard 3d 
///          management system.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame3d__
#define __Viewer_Frame3d__

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <string>

#include <Viewer/Frame.hh>
#include <Viewer/Module3dFactory.hh>

namespace Viewer
{
  class Camera3d;

class Frame3d : public Frame
{
public:
  Frame3d( RectPtr rect );
  virtual ~Frame3d();
  /// Deal with a new UI event
  void NewEvent( const Event& event );
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* configTable );
  /// Process event data
  virtual void ProcessEvent( const RenderState& renderState );
  /// Process run data
  virtual void ProcessRun();
  /// Render all 2d objects
  virtual void Render2d( RWWrapper& renderApp,
                         const RenderState& renderState ) { };
  /// Render all 3d objects
  virtual void Render3d( RWWrapper& renderApp,
                         const RenderState& renderState );
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp, 
                  const RenderState& renderState );
protected:
  /// Create a camera
  void SetCamera( const std::string& cameraName,
                  const sf::Rect<double>& cameraSize );
  /// Add a new module
  void AddModule( const std::string& moduleName,
                  const sf::Rect<double>& guiSize );
private:
  Camera3d* fCamera; /// < Must have a camera module
  std::vector<Module3d*> fModules; /// < The 3d Modules

  static Module3dFactory fsModule3dFactory; /// < The 3d Modules Factory
};

} //::Viewer

#endif
