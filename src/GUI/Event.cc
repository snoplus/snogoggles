#include <Viewer/Event.hh>
#include <Viewer/Rect.hh>
using namespace Viewer;

Event::Event( sf::Event& event )
  : sf::Event( event )
{ 

}

sf::Vector2<double> 
Event::GetPos() const
{
  sf::Vector2<double> pos;
  switch( this->Type )
    {
    case MouseButtonPressed:
    case MouseButtonReleased:
      pos = sf::Vector2<double>( this->MouseButton.X, this->MouseButton.Y );
      break;
    case MouseMoved:
      pos = sf::Vector2<double>( this->MouseMove.X, this->MouseMove.Y );
      break;
    }
  sf::Vector2<double> windowSize = Rect::GetWindowSize();
  sf::Vector2<double> windowRes = Rect::GetWindowResolution();
  pos.x = pos.x * windowRes.x / windowSize.x;
  pos.y = pos.y * windowRes.y / windowSize.y;
  return pos;
}
