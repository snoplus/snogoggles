////////////////////////////////////////////////////////////////////////
/// \class Viewer::Module3d
///
/// \brief   The base class for all 3d modules
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original Module3d class to take account
///          of codebase changes.
///          Implements functionality that is shared by the camera, hit,
///          track, geo and fitter modules. Also provides a nice abstraction
///          for organizing these 5 different modules. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Module3d__
#define __Viewer_Module3d__

#include <queue>
#include <string>

#include <Viewer/GUIEvent.hh>
#include <Viewer/GUIManager.hh>

namespace Viewer
{
  class ConfigurationTable;
  class RenderState;

class Module3d 
{
public:
  Module3d( RectPtr rect );

  virtual ~Module3d();
  /// Deal with a new UI event
  void NewEvent( const Event& event );
  /// The event loop
  virtual void EventLoop() = 0;
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable ) = 0;
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable ) = 0;
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* configTable ) = 0;
  /// Process data into renderable format
  virtual void ProcessData( const RenderState& renderState ) = 0;
  /// Render all 3d objects
  virtual void Render3d() = 0;
  /// Return the module name
  virtual std::string GetName() = 0;
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp );
protected:
  RectPtr fRect; /// < The module rect
  GUIManager fGUIManager; /// < The GUI Manager
  std::queue<GUIEvent> fEvents; /// < The events queue (GUI events are stored here)
};

} //::Viewer

#endif
