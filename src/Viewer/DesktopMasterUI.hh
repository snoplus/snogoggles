////////////////////////////////////////////////////////////////////////
/// \class Viewer::DesktopMasterUI
///
/// \brief   UI to control which desktop is visible
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class stores which desktop is currently visible and
///          supplies buttons to change between.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DesktopMasterUI__
#define __Viewer_DesktopMasterUI__

#include <SFML/System/Vector2.hpp>

#include <queue>

#include <Viewer/GUIEvent.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/GUIManager.hh>

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class RenderState;
  class Event;
namespace GUIs
{
  class RadioCheckBoxes;
}

class DesktopMasterUI
{
public:
  DesktopMasterUI( RectPtr rect,
		   unsigned int numDesktops );
  /// Deal with a new UI event
  void NewEvent( const Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable& configTable );
  /// Initialise without a configuration
  void Initialise();
  /// Load a configuration
  void LoadConfiguration( ConfigurationTable& configTable );
  /// Render the GUI objects
  void Render( RWWrapper& renderApp );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );
  /// Get the index of the currently displayed desktop
  inline unsigned int GetCurrentDesktop();
private:
  GUIManager fGUIManager; /// < GUI manager
  std::queue<GUIEvent> fEvents; /// < Returned gui events
  RectPtr fRect; /// < The DMUI drawable area
  unsigned int fNumDesktops; /// < Number of desktops
  unsigned int fCurrentDesktop; /// < Currently displayed desktop
  GUIs::RadioCheckBoxes* fDesktopRadio; /// < Desktop chooser radio
};

inline bool
DesktopMasterUI::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

inline unsigned int
DesktopMasterUI::GetCurrentDesktop()
{
  return fCurrentDesktop;
}

} //::Viewer

#endif
