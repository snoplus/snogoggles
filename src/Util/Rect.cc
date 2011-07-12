#include <SFML/OpenGL.hpp>

#include <Viewer/Coord.hh>
#include <Viewer/Rect.hh>
using namespace Viewer;

void 
Rect::SetFromWindowRect( const sf::Rect<double>& windowRect )
{
  sf::Vector2<double> windowCoord( windowRect.Left, windowRect.Top );
  SetFromWindowCoord( windowCoord );
  fSize = sf::Vector2<double>( windowRect.Width / fsWindowWidth * fsResolutionWidth,
			       windowRect.Height / fsWindowHeight * fsResolutionHeight );
}

void 
Rect::SetFromResolutionRect( const sf::Rect<double>& resolutionRect )
{
  sf::Vector2<double> resolutionCoord( resolutionRect.Left, resolutionRect.Top );
  SetFromResolutionCoord( resolutionCoord );
  fSize = sf::Vector2<double>( resolutionRect.Width, resolutionRect.Height );
}
  
void Rect::SetFromLocalRect( const sf::Rect<double>& localRect, Rect& motherRect )
{
  sf::Vector2<double> localCoord( localRect.Left, localRect.Top );
  SetFromLocalCoord( localCoord, motherRect );
  sf::Rect<double> resolutionRect = motherRect.GetResolutionRect();
  fSize = sf::Vector2<double>( localRect.Width * resolutionRect.Width,
			    localRect.Height * resolutionRect.Height );
}

sf::Rect<double> 
Rect::GetLocalRect( Rect& motherRect )
{
  sf::Vector2<double> localPos = GetLocalCoord( motherRect );
  sf::Rect<double> resolutionRect = motherRect.GetResolutionRect();
  sf::Vector2<double> localSize = sf::Vector2<double>( fSize.x / resolutionRect.Width,
						       fSize.y / resolutionRect.Height );
  return sf::Rect<double>( localPos.x, localPos.y, localSize.x, localSize.y );
}
  
sf::Rect<double> 
Rect::GetResolutionRect()
{
  sf::Vector2<double> resPos = GetResolutionCoord();
  return sf::Rect<double>( resPos.x, resPos.y, fSize.x, fSize.y );
}
 
sf::Rect<double> 
Rect::GetWindowRect()
{
  sf::Vector2<double> windowPos = GetWindowCoord();
  return sf::Rect<double>( windowPos.x, windowPos.y, 
			   fSize.x / fsResolutionWidth * fsWindowWidth, 
			   fSize.y / fsResolutionHeight * fsWindowHeight );
}

void 
Rect::SetAsGLViewport()
{
  // Remember Rect is defined as top left, viewport as bottom left
  sf::Rect<double> windowRect = GetWindowRect();
  glViewport( windowRect.Left, fsWindowHeight - ( windowRect.Top + windowRect.Height ), windowRect.Width, windowRect.Height );
}

sf::Rect<double>
Rect::GetViewport()
{
  sf::Rect<double> windowRect = GetWindowRect();
  windowRect.Top = fsWindowHeight - ( windowRect.Top + windowRect.Height );
  return windowRect;
}

bool 
Rect::ContainsResolutionPoint( const sf::Vector2<double>& point )
{
  sf::Rect<double> resolutionRect = GetResolutionRect();
  if( point.x > resolutionRect.Left && point.x < resolutionRect.Left + resolutionRect.Width && 
      point.y > resolutionRect.Top && point.y < resolutionRect.Top + resolutionRect.Height )
    return true;
  else
    return false;
}
 
bool 
Rect::ContainsLocalPoint( const sf::Vector2<double>& point, Rect& motherRect )
{
  sf::Rect<double> localRect = GetLocalRect( motherRect );
  if( point.x > localRect.Left && point.x < localRect.Left + localRect.Width && 
      point.y > localRect.Top && point.y < localRect.Top + localRect.Height )
    return true;
  else
    return false;
}
