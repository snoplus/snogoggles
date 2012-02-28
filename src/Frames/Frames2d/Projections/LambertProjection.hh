////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::LambertProjection
///
/// \brief   Displays PMT hits in the Lambert azimuthal equal area projection
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     10/07/11 : P.Jones - First Revision, new file. \n
///     21/02/12 : P.Jones - Second Revision, refactor to common 
///                          projection base class. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_LambertProjection__
#define __Viewer_Frames_LambertProjection__

#include <SFML/System/Vector2.hpp>

#include <Viewer/ProjectionMapArea.hh>
#include <Viewer/Vector3.hh>

namespace Viewer
{
namespace Frames
{

class LambertProjection : public ProjectionMapArea
{
public:
  LambertProjection( RectPtr rect ) : ProjectionMapArea( rect ) { }

  std::string GetName() { return LambertProjection::Name(); }

  static std::string Name() { return std::string( "Lambert" ); }

private:
  sf::Vector2<double> Project( Vector3 pmtPos );
};

} // ::Frames

} // ::Viewer

#endif
