////////////////////////////////////////////////////////////////////////
/// \class Viewer::PixelImage
///
/// \brief   Pixel image for drawing upon
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     31/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Quick way to draw very many objects in a pixel area. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_PixelImage__
#define __Viewer_PixelImage__

#include <SFML/System/Vector2.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Viewer/Rect.hh>

namespace Viewer
{
  class Colour;
  class Rect;

class PixelImage
{
public:
  PixelImage() { fPixels = NULL; }

  void Clear( Rect& rect );

  sf::Sprite ToSprite();

protected:
  Rect fRect;
  sf::Image fImage;  /// < SFML image, must exist in memory
  sf::Uint8* fPixels; /// < Pixel buffer RGBA (as word)
  int fWidth;  /// < Image width in pixels
  int fHeight; /// < Image height in pixels
};

} // ::Viewer

#endif
