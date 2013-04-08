#include <Viewer/TrackFrame3d.hh>
#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/Axes3d.hh>
using namespace Viewer;
using namespace Viewer::Frames;

TrackFrame3d::TrackFrame3d( RectPtr rect )
  : Frame3d( rect )
{
  SetCamera( Arcball3d::Name(), sf::Rect<double>( 0 , 0 , 0.8 , 0.8 ) );
  AddModule( Geodesic3d::Name(), sf::Rect< double >( 0.05, 0.9, 0.25, 0.05 ) );
  AddModule( Axes3d::Name(), sf::Rect< double >( 0.7, 0.9, 0.25, 0.05 ) );
  AddModule( DefaultTracks3d::Name(), sf::Rect< double >( 0.8, 0, 0.2, 0.6 ) );
}
