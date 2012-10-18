#include <SFML/Graphics/Rect.hpp>

#include <Viewer/ProjectionImage.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Colour.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

void 
ProjectionImage::DrawDot( const sf::Vector2<double>& position,
			  const Colour& colour )
{
  sf::Vector2<int> posPixel( static_cast<int>( position.x * fWidth ), 
			     static_cast<int>( position.y * fHeight ) );
  DrawSquare( posPixel, sf::Vector2<int>( 1, 1 ), colour );
}

void
ProjectionImage::DrawSquare( const sf::Vector2<int>& position,
			     const sf::Vector2<int>& size,
			     const Colour& colour )
{
  const int startX = position.x;
  int endX = startX + size.x;
  if( endX >= fWidth )
    endX = fWidth - 1;
  const int startY = position.y;
  int endY = startY + size.y;
  if( endY >= fHeight )
    endY = fHeight - 1;
  if( startX < 0 || startY < 0 || endX >= fWidth || endY >= fHeight )
    // Bad coordinates given
    return;

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
ProjectionImage::DrawSquare( const sf::Vector2<double>& position,
			     const Colour& colour )
{
  sf::Vector2<int> posPixel( static_cast<int>( position.x * fWidth ), 
                             static_cast<int>( position.y * fHeight ) );
  DrawSquare( posPixel, fSquareSize, colour );
}

void 
ProjectionImage::DrawSquare( const sf::Vector2<double>& position,
			     const sf::Vector2<double>& size,
			     const Colour& colour )
{
  sf::Vector2<int> posPixel( static_cast<int>( position.x * fWidth ), 
			     static_cast<int>( position.y * fHeight ) ); 
  sf::Vector2<int> sizePixel( static_cast<int>( size.x * fWidth ), 
			      static_cast<int>( size.y * fHeight ) ); 
  DrawSquare( posPixel, sizePixel, colour );
}

void
ProjectionImage::DrawHollowSquare( const sf::Vector2<double>& position,
				   const Colour& colour )
{
  sf::Vector2<int> posPixel( static_cast<int>( position.x * fWidth ), 
			     static_cast<int>( position.y * fHeight ) ); 
  DrawSquare( posPixel, fSquareSize, colour );
  sf::Vector2<int> newPos( posPixel.x + 1, posPixel.y + 1 );
  sf::Vector2<int> newSize( fSquareSize.x - 2, fSquareSize.y - 2 );
  DrawSquare( newPos, newSize, Colour() );
}

void
ProjectionImage::DrawHollowSquare( const sf::Vector2<double>& position,
				   const sf::Vector2<double>& size,
				   const Colour& colour )
{
  sf::Vector2<int> posPixel( static_cast<int>( position.x * fWidth ), 
			     static_cast<int>( position.y * fHeight ) ); 
  sf::Vector2<int> sizePixel( static_cast<int>( size.x * fWidth ), 
			      static_cast<int>( size.y * fHeight ) ); 
  DrawSquare( posPixel, sizePixel, colour );
  sf::Vector2<int> newPos( posPixel.x + 2, posPixel.y + 2 );
  sf::Vector2<int> newSize( sizePixel.x - 4, sizePixel.y - 4 );
  DrawSquare( newPos, newSize, GUIProperties::GetInstance().GetGUIColourPalette().GetBackground() );
}

void 
ProjectionImage::SetSquareSize( const sf::Vector2<double>& size )
{
  fSquareSize = sf::Vector2<int>( static_cast<int>( size.x * fWidth ), 
				  static_cast<int>( size.y * fHeight ) ); 
  if( fSquareSize.x < 1 )
    fSquareSize.x = 1;
  if( fSquareSize.y < 1 )
    fSquareSize.y = 1;
}

sf::Vector2<double>
ProjectionImage::GetSquareSize()
{
  return sf::Vector2<double>( static_cast<double>( fSquareSize.x ) / static_cast<double>( fWidth ), 
                              static_cast<double>( fSquareSize.y ) / static_cast<double>( fHeight ) );
}
