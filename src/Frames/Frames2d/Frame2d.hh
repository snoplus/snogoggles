////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame2d
///
/// \brief   The base class for all 2d frames
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  All 2d frames derive from this, adds the standard 2d GUI
///          management system.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame2d__
#define __Viewer_Frame2d__

#include <queue>
#include <string>

#include <Viewer/Frame.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/GUIManager.hh>

namespace Viewer
{

class Frame2d : public Frame
{
public:
  Frame2d( RectPtr rect );

  virtual ~Frame2d();
  /// Deal with a new UI event
  void NewEvent( const Event& event );
  /// Render the GUI objects
  void RenderGUI( RWWrapper& renderApp, 
                  const RenderState& renderState );
  /// Render all 3d objects
  void Render3d( RWWrapper& renderApp,
                 const RenderState& renderState ) { };
protected:
  GUIManager fGUIManager; /// < The GUI Manager
  std::queue<GUIEvent> fEvents; /// < The events queue (GUI events are stored here)
};

} //::Viewer

#endif
