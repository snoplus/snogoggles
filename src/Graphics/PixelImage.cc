#include <Viewer/PixelImage.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

void
PixelImage::Construct()
{
  fPixels = new sf::Uint8[fWidth * fHeight * 4];
  fTexture.create( fWidth, fHeight );
}

void
PixelImage::Clear()
{
  Clear( GUIProperties::GetInstance().GetGUIColourPalette().GetBackground() );
}

void 
PixelImage::Clear( Colour fillColour )
{
  const unsigned int pixelSize = fWidth * fHeight * 4;
  for( unsigned int iPixel = 0; iPixel < pixelSize; iPixel+=4 )
    {
      fPixels[iPixel]     = fillColour.r;
      fPixels[iPixel + 1] = fillColour.g;
      fPixels[iPixel + 2] = fillColour.b;
      fPixels[iPixel + 3] = fillColour.a;      
    }
  Update();
}
