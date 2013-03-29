////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Scaler
///
/// \brief   A horizontal bar with two moving vertical bars
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     28/03/13 : P.Jones - First Revision, new file. \n
///
/// \detail  Used for scaling objects
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Scaler__
#define __Viewer_GUIs_Scaler__

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
  class ProjectionImage;
namespace GUIs
{

class Scaler : public GUI
{
public:
  /// Defines which vertical bar is moving
  enum EState { eNormal, eScalingMin, eScalingMax };
  
  Scaler( RectPtr rect, 
          unsigned int guiID );
  virtual ~Scaler();
 
  void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  inline void SetState( const double min, 
                        const double max );
  inline double GetMin() const;
  inline double GetMax() const;
  inline void Reset();
protected:
  double fMinValue; /// < The current left/min vertical value
  double fMaxValue; /// < The current right/max vertical value
  EState fState; /// < Current state (which bar is moving)
  ProjectionImage* fImage; /// < Image on which to draw the bars
};

inline void
Scaler::SetState( const double min,
                      const double max )
{
  fMinValue = min;
  fMaxValue = max;
}

inline double
Scaler::GetMin() const
{
  return fMinValue;
}

inline double
Scaler::GetMax() const
{
  return fMaxValue;
}

inline void
Scaler::Reset()
{
  fMinValue = 0.0;
  fMaxValue = 0.99;
}

} // ::GUIs

} // ::Viewer

#endif
