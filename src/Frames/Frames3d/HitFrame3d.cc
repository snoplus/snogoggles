#include <Viewer/HitFrame3d.hh>
#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultHits3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/Axes3d.hh>
#include <Viewer/Fibre3d.hh>
using namespace Viewer;
using namespace Viewer::Frames;

HitFrame3d::HitFrame3d( RectPtr rect )
  : Frame3d( rect )
{
  SetCamera( Arcball3d::Name(), sf::Rect<double>( 0.05 , 0 , 0.9 , 0.9 ) );
  AddModule( Geodesic3d::Name(), sf::Rect< double >( 0.05, 0.95, 0.2, 0.05 ) );
  AddModule( DefaultHits3d::Name(), sf::Rect< double >( 0.05, 0.9, 0.4, 0.05 ) );
  AddModule( Axes3d::Name(), sf::Rect< double >( 0.5, 0.9, 0.3, 0.05 ) );
  AddModule( Fibre3d::Name(), sf::Rect< double >( 0.3, 0.95, 0.6, 0.05 ) );
}
