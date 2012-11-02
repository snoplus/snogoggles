////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::IcosahedralProjection
///
/// \brief   Displays PMT hits in the Icosahedral azimuthal equal area projection
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

#ifndef __Viewer_Frames_IcosahedralProjection__
#define __Viewer_Frames_IcosahedralProjection__

#include <TVector2.h>

#include <SFML/System/Vector2.hpp>

#include <Viewer/ProjectionMapArea.hh>
#include <Viewer/Vector3.hh>

namespace Viewer
{
namespace Frames
{

class IcosahedralProjection : public ProjectionMapArea
{
public:
  IcosahedralProjection( RectPtr rect ) : ProjectionMapArea( rect ) { }

  void PostInitialise( const ConfigurationTable* configTable );

  std::string GetName() { return IcosahedralProjection::Name(); }

  static std::string Name() { return std::string( "Icosahedral" ); }

  double GetAspectRatio() const { return 0.5; }
private:
  void DrawOutline();

  sf::Vector2<double> Project( Vector3 pmtPos );

  void ProjectOutline( TVector2 v1,
                       TVector2 v2 );
  
  std::vector< sf::Vector2<double> > fProjectedOutline; /// < The outline of the projection
};

} // ::Frames

} // ::Viewer

#endif
