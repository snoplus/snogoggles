#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <sstream>
#include <string.h>
using namespace std;

#include <Viewer/GUITextureManager.hh>
using namespace Viewer;

GUITextureManager::GUITextureManager()
{
  Initialise();
}

GUITextureManager::~GUITextureManager()
{
  ClearTextures();
}

void
GUITextureManager::ClearTextures()
{
  for( GUIRectMap::iterator iTer = fSubRects.begin(); iTer != fSubRects.end(); iTer++ )
    {
      delete (fTextures[iTer->first])[eBase];
      (fTextures[iTer->first])[eBase] = NULL;
      delete (fTextures[iTer->first])[eHighlight];
      (fTextures[iTer->first])[eHighlight] = NULL;
      delete (fTextures[iTer->first])[eActive];
      (fTextures[iTer->first])[eActive] = NULL;
    }
  fTextures.clear();
  fSubRects.clear();
  if( fBasePixels )
    {
      delete[] fBasePixels;
      fBasePixels = NULL;
    }
  fBaseWidth = 0;
  fBaseHeight = 0;
}

void
GUITextureManager::Initialise()
{
  sf::Image baseImage;
  stringstream fileLocation;
  fileLocation << getenv( "VIEWERROOT" ) << "/textures/GUIA.png";
  if( baseImage.LoadFromFile( fileLocation.str() ) )
    {
      fBaseWidth = baseImage.GetWidth();
      fBaseHeight = baseImage.GetHeight();
      const int pixels = fBaseWidth * fBaseHeight * 4;
      fBasePixels = new sf::Uint8[ pixels ];
      memcpy( fBasePixels, baseImage.GetPixelsPtr(), sizeof( sf::Uint8 ) * pixels );
    }
  else
    throw;
  fSubRects[eBarLeft] = sf::Rect<int>( 0, 0, 20, 20 );
  fSubRects[eBar] = sf::Rect<int>( 20, 0, 20, 20 );
  fSubRects[eBarRight] = sf::Rect<int>( 120, 0, 20, 20 );
  fSubRects[eDecrease] = sf::Rect<int>( 40, 0, 20, 20 );
  fSubRects[eIncrease] = sf::Rect<int>( 60, 0, 20, 20 );
  fSubRects[ePlus] = sf::Rect<int>( 80, 0, 20, 20 );
  fSubRects[eCross] = sf::Rect<int>( 100, 0, 20, 20 );
  fSubRects[eOpenBox] = sf::Rect<int>( 140, 0, 20, 20 );
  fSubRects[eCrossBox] = sf::Rect<int>( 160, 0, 20, 20 );
  fSubRects[eNewFrameLeft] = sf::Rect<int>( 0, 20, 20, 20 );
  fSubRects[eNewFrame] = sf::Rect<int>( 20, 20, 20, 20 );
  fSubRects[eNewFrameRight] = sf::Rect<int>( 40, 20, 20, 20 );
  // NULL init
  for( GUIRectMap::iterator iTer = fSubRects.begin(); iTer != fSubRects.end(); iTer++ )
    {
      (fTextures[iTer->first])[eBase] = NULL;
      (fTextures[iTer->first])[eHighlight] = NULL;
      (fTextures[iTer->first])[eActive] = NULL;
    }
  ChangeColourScheme();
}

sf::Texture* 
GUITextureManager::GetTexture( EGUITexture image,
			       EGUITextureState state )
{
  return (fTextures[image])[state];
}

void
GUITextureManager::ChangeColourScheme()
{
  for( GUIRectMap::iterator iTer = fSubRects.begin(); iTer != fSubRects.end(); iTer++ )
    {
      Colourise( iTer->first, eBase );
      Colourise( iTer->first, eHighlight );
      Colourise( iTer->first, eActive );
    }
}

void 
GUITextureManager::Colourise( EGUITexture image,
                              EGUITextureState state )
{
  GUIColourPalette* palette = GUIColourPalette::gPalette;
  sf::Rect<int> sourceRect = fSubRects[image];
  sf::Uint8* pixels = new sf::Uint8[ sourceRect.Width * sourceRect.Height * 4 ];
  for( int xPixel = 0; xPixel < sourceRect.Width; xPixel++ )
    {
      for( int yPixel = 0; yPixel < sourceRect.Height; yPixel++ )
	{
          const int basePixel = ( xPixel + sourceRect.Left + ( yPixel + sourceRect.Top ) * fBaseWidth ) * 4;
          Colour currentColour( fBasePixels[basePixel],
                                fBasePixels[basePixel + 1],
                                fBasePixels[basePixel + 2],
                                fBasePixels[basePixel + 3] );

          Colour pixelColour;
          pixelColour = palette->GetBaseColour( state );
          pixelColour = pixelColour.AddColourFraction( palette->GetBGColour( state ),
                                                       static_cast<double>( currentColour.g ) / 255.0 );
          pixelColour = pixelColour.AddColourFraction( palette->GetItemColour( state ),
                                                       static_cast<double>( currentColour.r ) / 255.0 );
          const int pixel = ( xPixel + yPixel * sourceRect.Width ) * 4;
          pixels[ pixel ] = pixelColour.r;
          pixels[ pixel + 1 ] = pixelColour.g;
          pixels[ pixel + 2 ] = pixelColour.b;
          pixels[ pixel + 3 ] = pixelColour.a;
        }
    }
  // Now produce the texture
  if( (fTextures[image])[state] == NULL )
    {
      (fTextures[image])[state] = new sf::Texture();
      (fTextures[image])[state]->Create( sourceRect.Width, sourceRect.Height );
    }
  (fTextures[image])[state]->Update( pixels );
}
