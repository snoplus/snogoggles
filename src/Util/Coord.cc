#include <SFML/Graphics/Rect.hpp>

#include <Viewer/Coord.hh>
#include <Viewer/Rect.hh>
using namespace Viewer;

double Coord::fsWindowWidth = 0.0;
double Coord::fsWindowHeight = 0.0;
double Coord::fsResolutionWidth = 0.0;
double Coord::fsResolutionHeight = 0.0;

void 
Coord::SetFromWindowCoord( const sf::Vector2<double>& windowCoord )
{
  fPosition = sf::Vector2<double>( windowCoord.x / fsWindowWidth * fsResolutionWidth, 
				   windowCoord.y / fsWindowHeight * fsResolutionHeight );
}

void 
Coord::SetFromResolutionCoord( const sf::Vector2<double>& resolutionCoord )
{
  fPosition = resolutionCoord;
}
  
void Coord::SetFromLocalCoord( const sf::Vector2<double>& localCoord, Rect& motherRect )
{
  sf::Rect<double> resolutionRect = motherRect.GetResolutionRect();
  fPosition = sf::Vector2<double>( localCoord.x * resolutionRect.Width + resolutionRect.Left,
				   localCoord.y * resolutionRect.Height + resolutionRect.Top );
}

sf::Vector2<double> 
Coord::GetLocalCoord( Rect& motherRect )
{
  sf::Rect<double> resolutionRect = motherRect.GetResolutionRect();
  return sf::Vector2<double>( ( fPosition.x - resolutionRect.Left ) / resolutionRect.Width,
			      ( fPosition.y - resolutionRect.Top ) / resolutionRect.Height );
}
  
sf::Vector2<double> 
Coord::GetResolutionCoord()
{
  return fPosition;
}
 
sf::Vector2<double> 
Coord::GetWindowCoord()
{
  return sf::Vector2<double>( fPosition.x / fsResolutionWidth * fsWindowWidth, 
			      fPosition.y / fsResolutionHeight * fsWindowHeight );
}

sf::Vector2<double>
Coord::GetGLCoord()
{
  sf::Vector2<double> windowCoord = GetWindowCoord();
  return sf::Vector2<double>( windowCoord.x, fsWindowHeight - windowCoord.y );
}

sf::Vector2<double>
Coord::GetGLRelativeCoord( Rect& motherRect )
{
  sf::Vector2<double> glCoord = GetGLCoord();
  sf::Rect<double> glRect = motherRect.GetViewport();
  return sf::Vector2<double>( ( glCoord.x - glRect.Left ) / glRect.Width, ( glCoord.y - glRect.Top ) / glRect.Height );
}
