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

#include <string>

#include <Viewer/RectPtr.hh>

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

class FrameMasterUI
{
public:
  FrameMasterUI( RectPtr rect );
  /// Deal with a new UI event, return frame name or ""
  std::string NewEvent( const Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable& configTable );
  /// Initialise without a configuration
  void Initialise();
  /// Load a configuration
  void LoadConfiguration( ConfigurationTable& configTable );
  /// Render all 2d objects
  void Render2d( RWWrapper& renderApp ) {}
  /// Render all 3d objects
  void Render3d( RWWrapper& renderApp ) {}
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );
private:
  RectPtr fRect; /// < The DMUI drawable area
};

inline bool
FrameMasterUI::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
