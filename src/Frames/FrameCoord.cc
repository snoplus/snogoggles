#include <Viewer/FrameCoord.hh>
using namespace Viewer;

sf::Vector2<double> 
FrameCoord::ToFrameCoord( const sf::Vector2<double>& resolutionCoord ) const
{

}

sf::Vector2<double> 
FrameCoord::ToResolutionCoord( const sf::Vector2<double>& frameCoord ) const
{

}
  
sf::Rect<double> 
FrameCoord::ToFrameRect( const sf::Rect<double>& resolutionRect ) const
{

}

sf::Rect<double> 
FrameCoord::ToResolutionRect( const sf::Rect<double>& frameRect ) const
{

}

sf::Rect<double> 
FrameCoord::Get3dViewport() const
{

}

sf::Rect<double> 
FrameCoord::GetFrameRect() const
{
  return fRect;
}
