////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameManager
///
/// \brief   The frame manager, manages all frames in a desktop
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     18/02/12 : P.Jones - New file, first revision \n
///     26/05/12 : P.Jones - Second Revision, refactor no grid.\n
///
/// \detail  This class manages the existance, position, creation and 
///          destruction of all frames in a desktop.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameManager__
#define __Viewer_FrameManager__

#include <SFML/System/Vector2.hpp>

#include <string>
#include <vector>

#include <Viewer/FrameEvent.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/FrameFactory.hh>

namespace Viewer
{
  class Event;
  class RenderState;
  class FrameContainer;
  class FrameMasterUI;
  class ConfigurationTable;
  class RWWrapper;
  class Frame;

class FrameManager
{
public:
  /// State of the Frame manager (is it moving a frame)
  enum EState { eNormal, eMoving, eResizing };

  FrameManager( RectPtr rect,
                double rightMargin,
                double bottomMargin );

  virtual ~FrameManager();
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
  /// Create a new frame, from FrameMasterUI
  void NewFrame( Frame* frame );
private:
  /// Create a new frame, locally called
  void NewFrame( unsigned int uFrame,
                 Frame* frame,
                 ConfigurationTable& configTable );
  /// Send an event to a frame container
  FrameEvent SendEvent( const int targetFrame,
                        const Event& event );
  /// Deal with the event returned by the frame
  void EventHandler( const FrameEvent& eventReturned );
  bool UpdateFrameRect( const int targetFrame,
                        sf::Rect<double> newRect );
  /// Update the frame position/size
  void UpdateFrameRect( const int targetFrame,
                        sf::Vector2<double> currentPosition );
  /// Find a frame by resolution coord
  int FindFrame( const sf::Vector2<double>& coord );
  /// Delete a frame
  void DeleteFrame( const int targetFrame );

  FrameFactory fFrameFactory; /// < The frame factory
  RectPtr fRect; /// < The frame manager rect
  RectPtr* fgRect; /// < The frame grid area rect
  FrameMasterUI* fFMUI; /// < The UI that controls which frames should be created.
  std::vector<FrameContainer*> fFrameContainers; /// < The frames themselves.
  sf::Vector2<double> fPressPosition; /// < Position (resolution) when mouse was pressed
  sf::Vector2<double> fPressOffset; /// < Vector between fPressPosition and frame top left on press, from top left to press pos
  int fFocus; /// < The current frame focus
  EState fState; /// < Current Frame manager state
  double fBottomMargin; /// < Local coord size of bottom margin
  double fRightMargin; /// < Local coord size of right margin
};

inline bool
FrameManager::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
