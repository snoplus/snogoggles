////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::ScalingBar
///
/// \brief   A scaler with a reset button
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     28/03/13 : P.Jones - First Revision, new file. \n
///
/// \detail  A scaler alongside a reset button
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_ScalingBar__
#define __Viewer_GUIs_ScalingBar__

#include <vector>
#include <string>

#include <Viewer/GUI.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
namespace GUIs
{
  class Scaler;

class ScalingBar : public GUI
{
public:
  /// Standard gui constructor
  ScalingBar( RectPtr rect, 
              unsigned int guiID );
  /// Destructor
  virtual ~ScalingBar();
  /// Render the objects
  void Render( RWWrapper& renderApp );
  /// Event handler
  GUIEvent NewEvent( const Event& event );
  /// Initialise the scaling bar
  void Initialise();

  void SetState( const double min,
                 const double max );
  double GetMin() const;
  double GetMax() const;
  void Reset();
protected:
  GUIManager fGUIManager; /// < Manage the persist labels
  Scaler* fScaler; /// < Pointer to the scaler
};

} // ::GUIs

} // ::Viewer

#endif
