#include <Viewer/FrameCoord.hh>
using namespace Viewer;

double FrameCoord::fsWindowWidth = 0.0;
double FrameCoord::fsWindowHeight = 0.0;
double FrameCoord::fsResolutionWidth = 0.0;
double FrameCoord::fsResolutionHeight = 0.0;

sf::Vector2<double> 
FrameCoord::WindowToResolutionCoord( const sf::Vector2<double>& windowCoord )
{
  return sf::Vector2<double>( windowCoord.x / fsWindowWidth * fsResolutionWidth, windowCoord.y / fsWindowHeight * fsResolutionHeight );
}
sf::Vector2<double> 
FrameCoord::ResolutionToWindowCoord( const sf::Vector2<double>& resolutionCoord )
{
  return sf::Vector2<double>( resolutionCoord.x / fsResolutionWidth * fsWindowWidth, resolutionCoord.y / fsResolutionHeight * fsWindowHeight );
}

sf::Rect<double> 
FrameCoord::WindowToResolutionRect( const sf::Rect<double>& windowRect )
{
  return sf::Rect<double>( windowRect.Left / fsWindowWidth * fsResolutionWidth,
			   windowRect.Top / fsWindowHeight * fsResolutionHeight,
			   windowRect.Width / fsWindowWidth * fsResolutionWidth,
			   windowRect.Height / fsWindowHeight * fsResolutionHeight );
}

sf::Rect<double> 
FrameCoord::ResolutionToWindowRect( const sf::Rect<double>& resolutionRect )
{
  return sf::Rect<double>( resolutionRect.Left / fsResolutionWidth * fsWindowWidth,
			   resolutionRect.Top / fsResolutionHeight * fsWindowHeight,
			   resolutionRect.Width / fsResolutionWidth * fsWindowWidth,
			   resolutionRect.Height / fsResolutionHeight *fsWindowHeight );
}

sf::Vector2<double> 
FrameCoord::ResolutionToFrameCoord( const sf::Vector2<double>& resolutionCoord ) const
{
  return sf::Vector2<double>( ( resolutionCoord.x - fRect.Left ) / fRect.Width, ( resolutionCoord.y - fRect.Top ) / fRect.Height );
}

sf::Vector2<double> 
FrameCoord::FrameToResolutionCoord( const sf::Vector2<double>& frameCoord ) const
{
  return sf::Vector2<double>( frameCoord.x * fRect.Width + fRect.Left, frameCoord.y * fRect.Height + fRect.Top );
}
  
sf::Rect<double> 
FrameCoord::ResolutionToFrameRect( const sf::Rect<double>& resolutionRect ) const
{
  return sf::Rect<double>( ( resolutionRect.Left - fRect.Left ) / fRect.Width,
			   ( resolutionRect.Top - fRect.Top ) / fRect.Height,
			   resolutionRect.Width / fRect.Width,
			   resolutionRect.Height / fRect.Height );
}

sf::Rect<double> 
FrameCoord::FrameToResolutionRect( const sf::Rect<double>& frameRect ) const
{
  return sf::Rect<double>( frameRect.Left * fRect.Width + fRect.Left,
			   frameRect.Top * fRect.Height + fRect.Top,
			   frameRect.Width * fRect.Width,
			   frameRect.Height * fRect.Height );
}

FrameCoord::FrameCoord()
{

}

FrameCoord::FrameCoord( sf::Rect<double>& rhs )
{
  fRect = rhs;
}

sf::Rect<double> 
FrameCoord::Get3dViewport() const
{
  sf::Rect<double> windowRect = ResolutionToWindowRect( fRect );
  return sf::Rect<double>( windowRect.Left,
			   fsWindowHeight - ( windowRect.Top + windowRect.Height ),
			   windowRect.Width,
			   windowRect.Height );
}

bool
FrameCoord::ContainsPoint( const sf::Vector2<double>& resolutionCoord ) const
{
  const double localX = resolutionCoord.x - fRect.Left;
  const double localY = resolutionCoord.y - fRect.Top;
  if( localX > 0 && localX < fRect.Width && localY > 0 && localY < fRect.Height )
    return true;
  else
    return false;
}
