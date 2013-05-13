////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame
///
/// \brief   The base class for all frames
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     19/02/12 : P.Jones - New file, first revision \n
///     06/04/13 : P.Jones - Refactor into 2d and 3d versions. \n
///
/// \detail  All frames derive from this base class. The base class deals
///          with the GUIManager.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame__
#define __Viewer_Frame__

#include <string>

#include <Viewer/RectPtr.hh>

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
  Frame( RectPtr rect ) : fRect( rect ) { }

  virtual ~Frame() { };

  /// Deal with a new UI event
  virtual void NewEvent( const Event& event ) = 0;
  /// The event loop
  virtual void EventLoop() = 0;
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable ) = 0;
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable ) = 0;
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* configTable ) = 0;
  /// Process event data
  virtual void ProcessEvent( const RenderState& renderState ) = 0;
  /// Process run data
  virtual void ProcessRun() = 0;
  /// Render all 2d objects
  virtual void Render2d( RWWrapper& renderApp, 
                         const RenderState& renderState ) = 0;
  /// Render all 3d objects
  virtual void Render3d( RWWrapper& renderApp, 
                         const RenderState& renderState ) = 0;
  /// Return the frame name
  virtual std::string GetName() = 0;
  /// Return the frames preferred aspect ratio, default to 1.0
  virtual double GetAspectRatio() const { return 1.0; }
  /// Render the GUI objects
  virtual void RenderGUI( RWWrapper& renderApp, 
                          const RenderState& renderState ) = 0;

  /// Ask if object contains a point
  //bool ContainsPoint( const sf::Vector2<double>& point ) { fRect->ContainsPoint( point, Rect::eResolution ); }
  /// Return the rect
  RectPtr GetRect() { return fRect; }
protected:
  RectPtr fRect; /// < The frame rect
};

} //::Viewer

#endif
