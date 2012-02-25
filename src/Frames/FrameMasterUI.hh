////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameMasterUI
///
/// \brief   UI to control which frame should be created
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class allows frames to be created.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameMasterUI__
#define __Viewer_FrameMasterUI__

#include <SFML/System/Vector2.hpp>

#include <queue>

#include <Viewer/RectPtr.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/FrameFactory.hh>

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class RenderState;
  class Event;
  class FrameManager;

namespace GUIs
{
  class NewFrameButton;
}

class FrameMasterUI
{
public:
  FrameMasterUI( RectPtr rect, 
		 RectPtr frameMotherRect,
		 FrameManager* frameManager );
  /// Deal with a new UI event, return frame name or ""
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
private:
  GUIManager fGUIManager; /// < The GUI manager
  RectPtr fRect; /// < The DMUI drawable area
  FrameFactory fFrameFactory; /// < Frame factory, contains frame types
  FrameManager* fFrameManager; /// < Pointer to the associated frame manager
  std::vector<GUIs::NewFrameButton*> fButtons; /// < Vector of frame buttons
  std::queue<GUIEvent> fEvents; /// < The events from the GUI objects
};

inline bool
FrameMasterUI::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
