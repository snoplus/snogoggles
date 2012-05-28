////////////////////////////////////////////////////////////////////////
/// \class Viewer::ColourMasterUI
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

#ifndef __Viewer_ColourMasterUI__
#define __Viewer_ColourMasterUI__

#include <SFML/System/Vector2.hpp>

#include <queue>

#include <Viewer/RectPtr.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/GUIManager.hh>

namespace sf
{
  class Colour;
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
  class Selector;
}


class ColourMasterUI
{
public:
  ColourMasterUI( RectPtr rect );
  ~ColourMasterUI();
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
private:
  RectPtr fRect; /// < The DMUI drawable area
  GUIManager fGUIManager; /// < The GUI manager
  std::queue<GUIEvent> fEvents;

  GUIs::Selector* fGUIColourSelector;
  GUIs::Selector* fColourSelector;
};

inline bool
ColourMasterUI::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
