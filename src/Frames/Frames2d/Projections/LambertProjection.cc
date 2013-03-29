#include <TVector3.h>

#include <cmath>
using namespace std;

#include <Viewer/LambertProjection.hh>
using namespace Viewer;
using namespace Viewer::Frames;

sf::Vector2<double>
LambertProjection::Project( sf::Vector3<double> channelPos )
{
  TVector3 pmtPos( channelPos.x, channelPos.y, channelPos.z );
  pmtPos = pmtPos.Unit();
  const double x = sqrt( 2 / ( 1 - pmtPos.z() ) ) * pmtPos.x() / 4.0 + 0.5; // Projected circle radius is 2 thus diameter 4
  const double y = sqrt( 2 / ( 1 - pmtPos.z() ) ) * pmtPos.y() / 4.0 + 0.5; // +0.5 such that x,y E [0, 1)
  return sf::Vector2<double>( x, y );
}
