////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::IcosahedralProjection
///
/// \brief   Event display using the "flattened" icosahedral projection
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     13.07.11 - Start
///     25/02/12 - P.Jones, Refactor to use ProjectionBase class, still
///                requires a further refactor for comments.
///
/// \detail  Not much more detail to go into here.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_IcosahedralProjection__
#define __Viewer_Frames_IcosahedralProjection__

#include <TVector2.h>
#include <TVector3.h>

#include <Viewer/Frame.hh>
#include <Viewer/ProjectionBase.hh>

namespace Viewer
{

namespace Frames
{

class IcosahedralProjection : public ProjectionBase
{
public:
  IcosahedralProjection( RectPtr rect );

  std::string GetName() { return IcosahedralProjection::Name(); }
  
  static std::string Name() { return std::string( "Icosahedral" ); }
  
private:
  sf::Vector2<double> Project( Vector3 pmtPos );
  sf::Vector2<double> Transform(
				int vertex3d_1, 
				int vertex3d_2, 
				int vertex3d_3, 
				int vertex2d_1, 
				int vertex2d_2, 
				int vertex2d_3, 
				TVector3 pmtPos);
  
  std::vector<TVector3> fVertex_centres;
  std::vector<TVector2> fVertex_edges;
  std::vector<TVector3> fVertices_3d;
  std::vector<TVector2> fVertices_2d;
  std::vector<TVector2> ficosPMTpos;
};

} // namespace Frames

} // namespace Viewer

#endif
