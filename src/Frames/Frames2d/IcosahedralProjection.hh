////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::IcosahedralProjection
///
/// \brief   Event display using the "flattened" icosahedral projection
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     13.07.11 - Start
///
/// \detail  Not much more detail to go into here.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_IcosahedralProjection__
#define __Viewer_Frames_IcosahedralProjection__

#include <TVector3.h>

#include <SFML/System/Vector2.hpp>

#include <Viewer/Frame.hh>
#include <Viewer/Shape.hh>

namespace Viewer
{
namespace Frames
{

class IcosahedralProjection:public Frame{
public:
  //empty classes
  void SaveConfiguration( ConfigurationTable& configTable );
  void Render3d() { }
  //set up the projection etc.
  //void Initialize(ConfigurationTable& configTable);
  void Initialise();
  //standard getting event stuff
  virtual void EventLoop();
  //classes dealing with name
  virtual std::string GetName() {return IcosahedralProjection::Name();}
  static std::string Name() {return std::string("IcosahedralProjection");}
  //actually draw it
  virtual void Render2d(RWWrapper& windowApp);

  /// 1.5 cols to every row
  double GetAspectRatio() { return 1.5; }

private:
  //figure out where PMT should be
  sf::Vector2<double> Projection(TVector3 pmtPos);
  sf::Vector2<double> Transform(int vertex3d_1, int vertex3d_2, int vertex3d_3, int vertex2d_1, int vertex2d_2, int vertex2d_3, TVector3 pmtPos);
  //use Phil's convention here 
  Shape fFilledPMT;
  Shape fOpenPMT;

  std::vector<TVector3> vertex_centres;
  std::vector<TVector2> vertex_edges;
  std::vector<TVector3> vertices_3d;
  std::vector<TVector2> vertices_2d;
  std::vector<TVector2> icosPMTpos;
};

} //end Frames
} //end Viewer

#endif
