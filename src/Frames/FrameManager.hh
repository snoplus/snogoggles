////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameManager
///
/// \brief   The frame manager, manages all frames in a desktop
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     18/02/12 : P.Jones - New file, first revision \n
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

#include <Viewer/FrameGrid.hh>
#include <Viewer/FrameEvent.hh>
#include <Viewer/RectPtr.hh>

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
  enum EState { eNormal, eMoving };

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
  /// Create a new frame 
  void NewFrame( Frame* frame );
private:

  FrameEvent DispatchEvent( const Event& event,
			    const int targetFrame );

  void EventHandler( const FrameEvent& retEvent );

  void ChangeState( const EState state );

  int FindFrame( const sf::Vector2<double>& coord );

  void DeleteFrame( const int targetFrame );

  void PositionFrame( const sf::Vector2<double>& coord,
		      const int targetFrame,
		      bool final );
  void ResizeFrame( const FrameGrid::ESize size,
		    const int targetFrame );

  RectPtr fRect; /// < The frame manager rect
  RectPtr* fgRect; /// < The frame grid area rect
  std::vector<FrameContainer*> fFrameContainers; /// < The frames themselves.
  sf::Vector2<double> fMoveOrigin; /// < Original position of the frame
  FrameMasterUI* fFMUI; /// < The UI that controls which frames should be created.
  FrameGrid* fFrameGrid; /// < Controls where frames can be positioned.
  int fFocus; /// < The current frame focus
  double fBottomMargin; /// < Local coord size of bottom margin
  double fRightMargin; /// < Local coord size of right margin
  EState fState; /// < Current Frame manager state
};

inline bool
FrameManager::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

} //::Viewer

#endif
