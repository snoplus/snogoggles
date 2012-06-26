////////////////////////////////////////////////////////////////////////
/// \class Viewer::DesktopPanel
///
/// \brief   Panel to control the desktop settings e.g. current
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     25/05/12 : P.Jones - New file, first revision \n
///
/// \detail  This panel deals with desktop selection
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DesktopPanel__
#define __Viewer_DesktopPanel__

#include <map>
#include <string>

#include <Viewer/Panel.hh>

namespace Viewer
{

class DesktopPanel : public Panel
{
public:
  DesktopPanel( RectPtr rect );
  ~DesktopPanel();
  /// Event handler
  virtual void NewEvent( const Event& event );
  /// The event loop
  virtual void EventLoop();
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* config );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* config );
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Get the current selected desktop
  inline unsigned int GetCurrentDesktop();
protected:
  /// Load the GUI configuration specific to the panel
  virtual void LoadGUIConfiguration( const ConfigurationTable* config );
  /// Change the currently displayed desktop
  void ChangeDesktop( const unsigned int newDesktop );

  unsigned int fCurrentDesktop;
};

inline unsigned int
DesktopPanel::GetCurrentDesktop()
{
  return fCurrentDesktop;
}

} //::Viewer

#endif
