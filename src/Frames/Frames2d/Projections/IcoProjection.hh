////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::IcoProjection
///
/// \brief   Displays PMT hits in the Ico azimuthal equal area projection
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

#ifndef __Viewer_Frames_IcoProjection__
#define __Viewer_Frames_IcoProjection__

#include <SFML/System/Vector2.hpp>

#include <Viewer/ProjectionMapArea.hh>
#include <Viewer/Vector3.hh>

namespace Viewer
{
namespace Frames
{

class IcoProjection : public ProjectionMapArea
{
public:
  IcoProjection( RectPtr rect ) : ProjectionMapArea( rect ) { }

  std::string GetName() { return IcoProjection::Name(); }

  static std::string Name() { return std::string( "Ico" ); }

  double GetAspectRatio() const { return 0.5; }

private:
  sf::Vector2<double> Project( Vector3 pmtPos );
};

} // ::Frames

} // ::Viewer

#endif
