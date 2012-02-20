#include <Viewer/PixelImage.hh>
using namespace Viewer;

void
PixelImage::Construct()
{
  fPixels = new sf::Uint8[fWidth * fHeight];
  fTexture.Create( fWidth, fHeight );
}

void 
PixelImage::Clear( Colour fillColour )
{
  const unsigned int pixelSize = fWidth * fHeight;
  for( unsigned int iPixel = 0; iPixel < pixelSize; iPixel+=4 )
    {
      fPixels[iPixel]     = fillColour.r;
      fPixels[iPixel + 1] = fillColour.g;
      fPixels[iPixel + 2] = fillColour.b;
      fPixels[iPixel + 3] = fillColour.a;      
    }
  Update();
}
