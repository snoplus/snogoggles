////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame
///
/// \brief   The base class for all frames
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///
/// \detail  All frames derive from this base class. The base class deals
///          with the GUIManager.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame__
#define __Viewer_Frame__

#include <queue>
#include <string>

#include <Viewer/RectPtr.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/GUIManager.hh>

namespace Viewer
{
  class RWWrapper;
  class ConfigurationTable;
  class RenderState;
  class Event;
  class GUIManager;

class Frame
{
public:
  enum EFrameType { eUtil, e3d, e2d };

  Frame( RectPtr rect );

  virtual ~Frame();

  inline void NewMother( RectPtr rect );
  /// Deal with a new UI event
  void NewEvent( const Event& event );
  /// The event loop
  virtual void EventLoop() = 0;
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without a configuration
  virtual void Initialise();
  /// Load a configuration
  virtual void LoadConfiguration( const ConfigurationTable* configTable );
  /// Render all 2d objects
  virtual void Render2d( RWWrapper& renderApp, 
                         const RenderState& renderState ) = 0;
  /// Render all 3d objects
  virtual void Render3d( RWWrapper& renderApp, 
                         const RenderState& renderState ) = 0;
  /// Return the frame name
  virtual std::string GetName() = 0;
  /// Return the frames preferred aspect ratio, default to 1.0
  virtual double GetAspectRatio() { return 1.0; }
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp, 
                  const RenderState& renderState );
  /// Ask if object contains a point
  inline bool ContainsPoint( const sf::Vector2<double>& point );

  inline RectPtr GetRect();
protected:
  RectPtr fRect; /// < The frame rect
  GUIManager fGUIManager;
  std::queue<GUIEvent> fEvents;
};

inline void
Frame::NewMother( RectPtr mother )
{
  fRect = mother;
  fGUIManager.NewMother( mother );
}

inline bool
Frame::ContainsPoint( const sf::Vector2<double>& point )
{
  return fRect->ContainsPoint( point, Rect::eResolution );
}

inline RectPtr
Frame::GetRect()
{
  return fRect;
}

} //::Viewer

#endif
