////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ProjectionMapArea
///
/// \brief   Extends the projection base to show the hit info via a MapArea
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     27/02/12 : P.Jones - First Revision, new file. \n
///
/// \detail  Displays the pmt hit info for the currently hovered over pmt.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ProjectionMapArea__
#define __Viewer_Frames_ProjectionMapArea__

#include <Viewer/ProjectionBase.hh>

namespace Viewer
{
  class GUIManager;
  class HitInfo;
namespace GUIs
{
  class MapArea;
}
namespace Frames
{

class ProjectionMapArea : public ProjectionBase
{
public:
  ProjectionMapArea( RectPtr rect ) : ProjectionBase( rect ), fPMTofInterest( -1 ) { }
  virtual ~ProjectionMapArea();

  virtual void Initialise();

  virtual void EventLoop();

  virtual void Render2d( RWWrapper& renderApp,
                         const RenderState& renderState );
protected:
  virtual sf::Vector2<double> Project( Vector3 pmtPos ) = 0;
  
  GUIs::MapArea* fMapArea; /// < The map area gui
  HitInfo* fHitInfo; /// < The hit info widget
  int fPMTofInterest; /// < The id of the current PMT of interest, default -1 (no interest)
};

} // ::Frames

} // ::Viewer

#endif
