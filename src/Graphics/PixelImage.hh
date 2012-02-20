////////////////////////////////////////////////////////////////////////
/// \class   Viewer::PixelImage
///
/// \brief   Pixel image for drawing upon
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     31/07/11 : P.Jones - First Revision, new file. \n
///     18/02/12 : P.Jones - Second Revision, use textures. \n
///
/// \detail  Quick way to draw very many objects in a pixel area. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_PixelImage__
#define __Viewer_PixelImage__

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Config.hpp>

#include <cmath>

#include <Viewer/RectPtr.hh>
#include <Viewer/Colour.hh>

namespace Viewer
{

class PixelImage
{
public:
  /// Constructor, must pass a Rect. Assumes you want the maximum texture size
  inline PixelImage( RectPtr rect,
		     const double aspectRatio = 1.0 );
  /// Constructor, must pass a Rect. Set the texture size
  inline PixelImage( RectPtr rect,
		     const int width, 
		     const int height );
  /// Clear the texture with a colour default white
  void Clear( Colour fillColour = Colour() );
  /// Must call after changes to the pixels
  inline void Update();
  /// Return the texture
  inline sf::Texture& GetTexture();
  /// Return the local Rect
  inline RectPtr GetRect();

protected:
  /// Construct the texture and pixels
  void Construct();

  RectPtr fLocalRect; /// < The text local rect
  sf::Texture fTexture; /// < SFML image, must exist in memory
  sf::Uint8* fPixels; /// < Pixel buffer RGBA (as word)
  int fWidth;  /// < Image width in pixels
  int fHeight; /// < Image height in pixels
};

inline 
PixelImage::PixelImage( RectPtr rect,
			const double aspectRatio )
  : fLocalRect(rect)
{
  int totalPixels = static_cast<int>( sf::Texture::GetMaximumSize() );
  // Calculate the maximum width at this aspectRatio
  fWidth = static_cast<int>( sqrt( static_cast<double>( totalPixels ) / aspectRatio ) );
  fHeight = static_cast<int>( fWidth * aspectRatio );
  Construct();
}

inline
PixelImage::PixelImage( RectPtr rect,
			const int width,
			const int height )
  : fLocalRect(rect)
{
  fWidth = width;
  fHeight = width;
  Construct();
}

inline void
PixelImage::Update()
{
  fTexture.Update( fPixels );
}

inline sf::Texture& 
PixelImage::GetTexture()
{
  return fTexture;
}

inline RectPtr 
PixelImage::GetRect()
{
  return fLocalRect;
}

} // ::Viewer

#endif
