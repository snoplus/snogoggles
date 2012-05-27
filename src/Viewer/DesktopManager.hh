////////////////////////////////////////////////////////////////////////
/// \class Viewer::DesktopManager
///
/// \brief   Manages the multiple desktops
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     18/02/12 : P.Jones - New file, first revision \n
///
/// \detail  This class owns the desktops and passes event information
///          through.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DesktopManager__
#define __Viewer_DesktopManager__

#include <vector>

#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class DesktopMasterUI;
  class ColourMasterUI;
  class Desktop;
  class RWWrapper;
  class ConfigurationTable;
  class Event;

class DesktopManager
{
public:
  DesktopManager( RectPtr globalMother, 
		  double rightMargin,
		  double bottomMargin );
  ~DesktopManager();
  /// Deal with a new UI event
  void NewEvent( Event& event );
  /// The event loop
  void EventLoop();
  /// Save the current configuration
  void SaveConfiguration( ConfigurationTable* config );
  /// Initialise without a configuration
  void Initialise();
  /// Load a configuration
  void LoadConfiguration( const ConfigurationTable* config );
  /// Draw all 2d objects
  void Render2d( RWWrapper& renderApp );
  /// Draw all 3d objects
  void Render3d( RWWrapper& renderApp );
  /// Draw the GUI objects
  void RenderGUI( RWWrapper& renderApp );
private:
  std::vector<Desktop*> fDesktops; /// < The available desktops
  RectPtr fGlobalMother; /// < The gloabl mother rect, this class does not need it's own
  DesktopMasterUI* fDMUI; /// < The UI which controls which desktop is visible
  ColourMasterUI* fCMUI; /// < The UI which controls the current colour scheme
  double fRightMargin; /// < Local coord size of right margin
  double fBottomMargin; /// < Local coord size of bottom margin
};

} //::Viewer

#endif
