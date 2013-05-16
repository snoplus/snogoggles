////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::AxisScaler
///
/// \brief   A horizontal axis with two moving vertical bars
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     16/05/13 : P.Jones - First Revision, new file. \n
///
/// \detail  Allows scaling along an axis
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_AxisScaler__
#define __Viewer_GUIs_AxisScaler__

#include <vector>

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
  class Event;
  class ProjectionImage;
namespace GUIs
{

class AxisScaler : public GUI
{
public:
  /// Defines which vertical bar is moving
  enum EState { eNormal, eScalingMin, eScalingMax, eBoth };
  
  AxisScaler( RectPtr rect, 
              unsigned int guiID );
  virtual ~AxisScaler();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  /// Reset 
  void Reset() { fMinValue = fMinLimit; fMaxValue = fMaxLimit; }
  /// Set the axis size (also functions as the zoom out)
  void SetLimits( const double min,
                  const double max );
  /// Get the current max
  double GetMax() const { return fMaxValue; }
  /// Get the current min
  double GetMin() const { return fMinValue; }
  /// Zoom in 
  void ZoomIn() { fMinLimit = fMinValue; fMaxLimit = fMaxValue; }
protected:
  /// Convert a local coord pos to a value
  double PosToValue( double pos ) const;
  /// Convert a value into a local coord
  double ValueToPos( double value ) const;
  

  std::vector<Text> fAxisText; /// < The axis text
  double fMaxLimit; /// < The upper limit
  double fMinLimit; /// < The lower limit
  double fMinValue; /// < The current left/min vertical value
  double fMaxValue; /// < The current right/max vertical value
  EState fState; /// < Current state (which bar is moving)
  ProjectionImage* fImage; /// < Image on which to draw the bars
};

} // ::GUIs

} // ::Viewer

#endif
