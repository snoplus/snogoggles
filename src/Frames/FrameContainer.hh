////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameContainer
///
/// \brief   Collection of the frame and the top bar GUIs
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class manages the frames top bar GUI and contains the 
///          frame itself. It also manages loading frames.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameContainer__
#define __Viewer_FrameContainer__

#include <SFML/System/Vector2.hpp>

#include <string>

#include <Viewer/RectPtr.hh>
#include <Viewer/FrameEvent.hh>

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class RenderState;
  class Event;
  class Frame;
  class TopBar;

class FrameContainer
{
public:
  FrameContainer( RectPtr rect );
  ~FrameContainer();
  /// Deal with a new UI event
  FrameEvent NewEvent( const Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  void PostInitialise( const ConfigurationTable* configTable );
  /// Render all 2d objects
  void Render2d( RWWrapper& renderApp, 
                 const RenderState& renderState );
  /// Render all 3d objects
  void Render3d( RWWrapper& renderApp, 
                 const RenderState& renderState );
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp, 
                  const RenderState& renderState );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );
  /// Ask if rect overlaps this rect
  inline bool Overlaps( const sf::Rect<double>& rect );

  inline const sf::Rect<double> GetRect( const Rect::ECoordSystem& system );
  /// Get the frames preferred aspect ratio
  double GetAspectRatio() const;

  void SetRect( const sf::Rect<double>& rect,
		const Rect::ECoordSystem& system );

  bool IsPinned();
  void SetFrame( Frame* frame ) { fFrame = frame; }
private:
  RectPtr fRect; /// < The container rect
  Frame* fFrame; /// < Pointer to the frame
  TopBar* fTopBar; /// < Pointer to the top bar GUI
};

inline bool
FrameContainer::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

inline bool
FrameContainer::Overlaps( const sf::Rect<double>& rect )
{
  return fRect->OverlapsRect( rect );
}

inline const sf::Rect<double>
FrameContainer::GetRect( const Rect::ECoordSystem& system )
{
  return fRect->GetRect( system );
}

} //::Viewer

#endif
