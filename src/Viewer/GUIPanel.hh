////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIPanel
///
/// \brief   Panel to control the gui settings e.g. colour
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     25/05/12 : P.Jones - New file, first revision \n
///
/// \detail  This panel deals with gui colours etc...
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIPanel__
#define __Viewer_GUIPanel__

#include <Viewer/Panel.hh>

namespace Viewer
{

class GUIPanel : public Panel
{
public:
  GUIPanel( RectPtr rect );
  ~GUIPanel();
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
};

} //::Viewer

#endif
