////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::LambertProjection
///
/// \brief   Displays PMT hits in the Lambert azimuthal equal area projection
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     10/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_LambertProjection__
#define __Viewer_Frames_LambertProjection__

#include <TVector3.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <Viewer/Frame.hh>
#include <Viewer/ProjectionImage.hh>
#include <Viewer/TimeAxis.hh>
#include <Viewer/Text.hh>

namespace RAT
{
namespace DS
{
  class PMTProperties;
}
}

namespace Viewer
{
namespace GUIs
{
  class MapArea;
}
namespace Frames
{

class LambertProjection : public Frame
{
public:
  void Initialise();
  void LoadConfiguration( ConfigurationTable& configTable );

  void SaveConfiguration( ConfigurationTable& configTable );

  virtual void EventLoop();
  
  virtual std::string GetName() { return LambertProjection::Name(); }
  
  static std::string Name() { return std::string( "LambertProjection" ); }

  virtual void Render2d( RWWrapper& windowApp );

  void Render3d() { }
private:
  sf::Vector2<double> Project( TVector3 pmtPos );

  sf::Rect<double> fProjectArea;
  sf::Rect<double> fAxisArea;
  ProjectionImage fImage;
  TimeAxis fTimeAxis;

  Text fInfoText;
  GUIs::MapArea* fMapArea; 
};

} // ::Frames

} // ::Viewer

#endif
