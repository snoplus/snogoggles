////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::ScalingBar
///
/// \brief   A Base class for button GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_ScalingBar__
#define __Viewer_GUIs_ScalingBar__

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
  class ProjectionImage;
namespace GUIs
{

class ScalingBar : public GUI
{
public:
  enum EState { eNormal, eScalingMin, eScalingMax };

  ScalingBar( RectPtr rect, 
              unsigned int guiID );
  virtual ~ScalingBar();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  inline void SetState( const double min, 
                        const double max );
  inline double GetMin() const;
  inline double GetMax() const;
  inline void Reset();
protected:
  double fMinValue;
  double fMaxValue;
  EState fState;
  ProjectionImage* fImage;
};

inline void
ScalingBar::SetState( const double min,
                      const double max )
{
  fMinValue = min;
  fMaxValue = max;
}

inline double
ScalingBar::GetMin() const
{
  return fMinValue;
}

inline double
ScalingBar::GetMax() const
{
  return fMaxValue;
}

inline void
ScalingBar::Reset()
{
  fMinValue = 0.0;
  fMaxValue = 0.99;
}

} // ::GUIs

} // ::Viewer

#endif
