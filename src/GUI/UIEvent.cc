#include <Viewer/UIEvent.hh>
#include <Viewer/Rect.hh>
using namespace Viewer;

UIEvent::UIEvent( sf::Event& event, Rect& motherRect )
  : sf::Event( event ), fMotherRect( motherRect )
{ 
  sf::Vector2<double> windowCoord;
  if( this->Type == MouseButtonPressed || this->Type == MouseButtonReleased )
    windowCoord = sf::Vector2<double>( MouseButton.X, MouseButton.Y );
  else if( this->Type == MouseMoved )
    windowCoord = sf::Vector2<double>( MouseMove.X, MouseMove.Y );

  fCoord.SetFromWindowCoord( windowCoord );
}

sf::Vector2<double> 
UIEvent::GetLocalCoord()
{
  if( this->Type != MouseButtonPressed && this->Type != MouseButtonReleased && this->Type != MouseMoved )
    return sf::Vector2<double>( -1.0, -1.0 );
  return fCoord.GetLocalCoord( fMotherRect );
}

sf::Vector2<double> 
UIEvent::GetResolutionCoord()
{  
  if( this->Type != MouseButtonPressed && this->Type != MouseButtonReleased && this->Type != MouseMoved )
    return sf::Vector2<double>( -1.0, -1.0 );
  return fCoord.GetResolutionCoord();
}
