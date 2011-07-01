#include <Viewer/UIEvent.hh>
using namespace Viewer;

sf::Vector2<double> 
UIEvent::GetLocalCoord()
{
  sf::Vector2<double> point;
  if( this->Type == MouseButtonPressed || this->Type == MouseButtonReleased )
    point = sf::Vector2<double>( MouseButton.X, MouseButton.Y );
  else if( this->Type == MouseMoved )
    point = sf::Vector2<double>( MouseMove.X, MouseMove.Y );
  else
    return point;
  point = FrameCoord::WindowToResolutionCoord( point );
  return fFrameCoord.ResolutionToFrameCoord( point );
}
