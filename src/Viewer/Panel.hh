////////////////////////////////////////////////////////////////////////
/// \class Viewer::Panel
///
/// \brief   Base class for panel GUIs
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     24/05/12 : P.Jones - New file, first revision \n
///
/// \detail  This is the base class for all the panel GUIs in the viewer.
///          This class loads the GUI configuration from the relevant 
///          xml file.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Panel__
#define __Viewer_Panel__

#include <vector>
#include <queue>
#include <map>
#include <string>

#include <Viewer/RectPtr.hh>
#include <Viewer/GUIManager.hh>

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class Event;
  class GUI;
  class Text;

class Panel
{
public:
  Panel( RectPtr rect,
         const std::string& guiConfigName );
  virtual ~Panel();
  /// Deal with a new UI event
  virtual void NewEvent( const Event& event );
  /// The event loop
  virtual void EventLoop() = 0;
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* config );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* config );
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable ) = 0;
  /// Render the GUI objects
  void Render( RWWrapper& renderApp );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );
  /// Set wether the panel is enabled
  void SetEnable( bool enable ) { fEnabled = enable; }
protected:
  /// Load the GUI configuration specific to the panel
  virtual void LoadGUIConfiguration( const ConfigurationTable* guiConfig ) = 0;

  RectPtr fRect; /// < The DMUI drawable area
  GUIManager fGUIManager; /// < The GUI manager
  std::queue<GUIEvent> fEvents; /// < The GUIEvents
  std::string fGUIConfigName; /// < The name of the GUI configuration

  std::map<int, GUI*> fGUIs; /// < The GUI Objects, mapped by effect To implement
  std::map<int, Text*> fLabels; /// < The label objects, mapped by result
  std::vector<Text*> fTexts; /// < Extra text objects

  bool fEnabled; /// < If false the frame is not drawn nor accepts events
private:
  Panel();
};

inline bool
Panel::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
