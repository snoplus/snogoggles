////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::EllipticalProjection
///
/// \brief   Event display using the elliptical or "Mollweide" projection
///
/// \author  Ken Clark <k.clark1@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25.07.11 - Start
///
/// \detail  Not much more detail to go into here.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_EllipticalProjection__
#define __Viewer_Frames_EllipticalProjection__

#include <TVector3.h>

#include <SFML/System/Vector2.hpp>

#include <Viewer/Frame.hh>
#include <Viewer/Shape.hh>
#include <Viewer/ProjectionImage.hh>

namespace Viewer
{
namespace Frames
{

class EllipticalProjection:public Frame{
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
  virtual std::string GetName() {return EllipticalProjection::Name();}
  static std::string Name() {return std::string("EllipticalProjection");}
  //actually draw it
  virtual void Render2d(RWWrapper& windowApp);
  virtual void FillPMTLocations();

private:
  //figure out where PMT should be
  sf::Vector2<double> Projection(TVector3 pmtPos);
  //use Phil's convention here 
  Shape fFilledPMT;
  Shape fOpenPMT;
  bool projFilled;

  std::vector<TVector3> vertex_centres;
  std::vector<TVector2> vertex_edges;
  std::vector<TVector3> vertices_3d;
  std::vector<TVector2> vertices_2d;
  std::vector<sf::Vector2<double> > projPosVec;
 
  sf::Rect<double> fProjectArea; 
  ProjectionImage fImage;

};

} //end Frames
} //end Viewer

#endif
