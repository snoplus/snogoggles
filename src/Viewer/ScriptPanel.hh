////////////////////////////////////////////////////////////////////////
/// \class Viewer::ScriptPanel
///
/// \brief   Panel to control the script settings
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     12/06/12 : P.Jones - New file, first revision \n
///
/// \detail  This panel deals with which scripts are active
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ScriptPanel__
#define __Viewer_ScriptPanel__

#include <Viewer/Panel.hh>

namespace Viewer
{

class ScriptPanel : public Panel
{
public:
  ScriptPanel( RectPtr rect );
  ~ScriptPanel();
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
private:
  enum { eAnalSelect = 0, eAnalRefresh = 1, eAnalOn = 2, eEventSelect = 3, eEventRefresh = 4, eEventOn = 5, 
         ePMTSelect = 6, ePMTRefresh = 7, ePMTOn = 8 };
};

} //::Viewer

#endif
