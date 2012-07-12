////////////////////////////////////////////////////////////////////////
/// \class Viewer::DesktopManager
///
/// \brief   Manages the multiple desktops
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     18/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class owns the desktops and passes event information
///          through.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DesktopManager__
#define __Viewer_DesktopManager__

#include <vector>

#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class DesktopPanel;
  class GUIPanel;
  class ScriptPanel;
  class Desktop;
  class RWWrapper;
  class ConfigurationTable;
  class Event;

class DesktopManager
{
public:
  DesktopManager( RectPtr globalMother );
  ~DesktopManager();
  /// Deal with a new UI event
  void NewEvent( Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable* config );
  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* config );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* config );
  /// Process data into renderable format
  void ProcessData( );
  /// Draw all 2d objects
  void Render2d( RWWrapper& renderApp );
  /// Draw all 3d objects
  void Render3d( RWWrapper& renderApp );
  /// Draw the GUI objects
  void RenderGUI( RWWrapper& renderApp );
private:
  std::vector<Desktop*> fDesktops; /// < The available desktops
  RectPtr fGlobalMother; /// < The gloabl mother rect, this class does not need it's own
  DesktopPanel* fDesktopPanel; /// < The panel which controls which desktop is visible
  GUIPanel* fGUIPanel; /// < The panel which controls the gui settings
  ScriptPanel* fScriptPanel; /// < The panel which controls the scripts
};

} //::Viewer

#endif
