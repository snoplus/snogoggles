////////////////////////////////////////////////////////////////////////
/// \class Viewer::ProjectionImage
///
/// \brief   Pixel image for projecting upon
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     31/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Quick way to draw very many squares in a pixel area. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ProjectionImage__
#define __Viewer_ProjectionImage__

#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Image.hpp>

#include <Viewer/Sprite.hh>
#include <Viewer/Rect.hh>

namespace Viewer
{
  class Colour;
  class Rect;

class ProjectionImage
{
public:
  ProjectionImage() { fPixels = NULL; }

  void Clear( Rect& rect );

  void DrawSquare( const sf::Vector2<double>& position, /// < In local Coords 
		   const sf::Vector2<double>& size,     /// < In local Coords
		   const Colour& colour );
  void DrawHollowSquare( const sf::Vector2<double>& position, /// < In local Coords 
			 const sf::Vector2<double>& size,     /// < In local Coords
			 const Colour& colour );

  Sprite ToSprite();

protected:
  Rect fRect;
  sf::Image fImage;  /// < SFML image, must exist in memory
  sf::Uint8* fPixels; /// < Pixel buffer RGBA (as word)
  int fWidth;  /// < Image width in pixels
  int fHeight; /// < Image height in pixels
};

} // ::Viewer

#endif
