////////////////////////////////////////////////////////////////////////
/// \class Viewer::EventMasterUI
///
/// \brief   UI to control which event is visible
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class stores which event properties are globally 
///          visible. I.e. show charge.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_EventMasterUI__
#define __Viewer_EventMasterUI__

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>

#include <queue>

#include <Viewer/RectPtr.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/RenderState.hh>

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class Event;
namespace GUIs
{
  class Selector;
  class RadioCheckBoxes;
  class ScalingBar;
}

class EventMasterUI
{
public:
  EventMasterUI( RectPtr rect );
  ~EventMasterUI();
  /// Deal with a new UI event
  void NewEvent( const Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable );
  /// Render the GUI objects
  void Render( RWWrapper& renderApp );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );
  /// Return the current render state
  RenderState GetRenderState();
private:
  RectPtr fRect; /// < The DMUI drawable area
  GUIManager fGUIManager; /// < The GUI manager
  std::queue<GUIEvent> fEvents;
  sf::Clock fClock; /// < Timing clock, for continuous events
  RenderState fCurrentRenderState; /// < The current render state

  GUIs::Selector* fRefreshSelector;
  GUIs::RadioCheckBoxes* fTypeRadio;
  GUIs::RadioCheckBoxes* fSourceRadio;
  GUIs::ScalingBar* fScalingBar;
};

inline bool
EventMasterUI::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
