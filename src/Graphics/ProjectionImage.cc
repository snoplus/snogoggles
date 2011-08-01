#include <SFML/Graphics/Rect.hpp>

#include <Viewer/ProjectionImage.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Colour.hh>
using namespace Viewer;

void 
ProjectionImage::DrawSquare( const sf::Vector2<double>& position,
			     const sf::Vector2<double>& size,
			     const Colour& colour )
{
  const int startX = position.x * fWidth;
  int endX = startX + size.x * fWidth;
  if( endX >= fWidth )
    endX = fWidth - 1;
  const int startY = position.y * fHeight;
  int endY = startY + size.y * fHeight;
  if( endY >= fHeight )
    endY = fHeight - 1;
  for( int xPixel = startX; xPixel <= endX; xPixel++ )
    for( int yPixel = startY; yPixel <= endY; yPixel++ )
      {
	int pixel = ( xPixel + yPixel * fWidth ) * 4;
	fPixels[pixel] = colour.r;
	fPixels[pixel + 1] = colour.g;
	fPixels[pixel + 2] = colour.b;
	fPixels[pixel + 3] = colour.a;
      }
}
void
ProjectionImage::DrawHollowSquare( const sf::Vector2<double>& position,
				   const sf::Vector2<double>& size,
				   const Colour& colour )
{
  DrawSquare( position, size, colour );
  double pixelWidth = 1.0 / static_cast<double>( fWidth );
  double pixelHeight = 1.0 / static_cast<double>( fHeight );
  sf::Vector2<double> newPos( position.x + pixelWidth, position.y + pixelHeight );
  sf::Vector2<double> newSize( size.x - 2.0 * pixelWidth, size.y - 2.0 * pixelHeight );
  DrawSquare( newPos, newSize, Colour() );
}
