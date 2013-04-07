#include <Viewer/FitterFrame3d.hh>
#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultFitter3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/Axes3d.hh>
using namespace Viewer;
using namespace Viewer::Frames;

FitterFrame3d::FitterFrame3d( RectPtr rect )
  : Frame3d( rect )
{
  SetCamera( Arcball3d::Name(), sf::Rect<double>( 0 , 0 , 0.8 , 0.8 ) );
  AddModule( Geodesic3d::Name(), sf::Rect< double >( 0.75, 0.96, 0.23, 0.04 ) );
  AddModule( Axes3d::Name(), sf::Rect< double >( 0.5, 0.96, 0.23, 0.04 ) );
  AddModule( DefaultFitter3d::Name(), sf::Rect< double >( 0.8, 0, 0.2, 0.92 ) );
}
