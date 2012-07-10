////////////////////////////////////////////////////////////////////////
/// \class Viewer::FramePanel
///
/// \brief   Panel to control the frames
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/06/12 : P.Jones - New file, first revision \n
///
/// \detail  This panel deals with frame creation/mass destruction.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FramePanel__
#define __Viewer_FramePanel__

#include <map>
#include <string>

#include <Viewer/Panel.hh>

namespace Viewer
{
  class FrameManager;

class FramePanel : public Panel
{
public:
  FramePanel( RectPtr rect,
              RectPtr frameRect, /// < Frame Mother Rect
              FrameManager& frameManager );
  ~FramePanel();
  /// The event loop
  virtual void EventLoop();
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* config );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* config );
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
protected:
  /// Load the GUI configuration specific to the panel
  virtual void LoadGUIConfiguration( const ConfigurationTable* config );

  FrameManager& fFrameManager; /// < Object that controls frames in this desktop
};

} //::Viewer

#endif
