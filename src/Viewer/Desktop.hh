////////////////////////////////////////////////////////////////////////
/// \class Viewer::Desktop
///
/// \brief   The Desktop
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     18/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class holds the desktop information and UI. Frames are 
///          managed by the FrameManager.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Desktop__
#define __Viewer_Desktop__

#include <SFML/System/Vector2.hpp>

#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class EventPanel;
  class FramePanel;
  class FrameManager;
  class Event;
  class ConfigurationTable;
  class RWWrapper;  

class Desktop
{
public:
  /// Construct with a rect and global margin sizes
  Desktop( RectPtr desktopRect );
  ~Desktop();
  /// Deal with a new UI event
  void NewEvent( Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable );
  /// Process Data into renderable format
  void ProcessData();
  /// Render all 2d objects
  void Render2d( RWWrapper& renderApp );
  /// Render all 3d objects
  void Render3d( RWWrapper& renderApp );
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp );
  /// Set screenshot mode (or not)
  void ToggleScreenshot( bool enable );
private:
  RectPtr fRect; /// < The desktop rect
  FrameManager* fFrameManager; /// < The frame maanager
  EventPanel* fEventPanel; /// < The GUI which controls the render state (Charge, Time, UnCal etc...)
  FramePanel* fFramePanel; /// < GUI control of the frame existance
  bool fScreenshotMode; /// < In screenshot mode?
};

} //::Viewer

#endif
