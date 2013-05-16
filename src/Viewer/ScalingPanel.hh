////////////////////////////////////////////////////////////////////////
/// \class Viewer::ScalingPanel
///
/// \brief   Panel to control the scaling and colour
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     16/05/13 : P.Jones - New file, first revision \n
///
/// \detail  This panel deals with scaling and gui colours etc...
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ScalingPanel__
#define __Viewer_ScalingPanel__

#include <Viewer/Panel.hh>
#include <Viewer/RenderState.hh>

namespace Viewer
{

class ScalingPanel : public Panel
{
public:
  ScalingPanel( RectPtr rect,
                RenderState& renderState );
  ~ScalingPanel();
  /// The event loop
  virtual void EventLoop();
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* config );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* config );
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
protected:
  /// Load the Scaling configuration specific to the panel
  virtual void LoadGUIConfiguration( const ConfigurationTable* config );

  RenderState& fRenderState; /// < Reference to the current desktop render state
private:
  enum { eScaling = 0, eScaleReset = 1, eScaleZoomIn = 2, eScaleZoomOut = 3, eInvertBG = 4, eSelectColour = 5 };
};

} //::Viewer

#endif
