#include <SFML/Graphics/Image.hpp>

#include <iostream>
#include <string.h>
using namespace std;

#include <Viewer/ImageManager.hh>
#include <Viewer/GUIImageManager.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Colour.hh>
#include <Viewer/GUIDefaultPalette.hh>
using namespace Viewer;

GUIImageManager* GUIImageManager::fGUIImageManager = NULL;
std::map< EGUIImage, sf::Rect<int> > GUIImageManager::fSubRectMap;

GUIImageManager::GUIImageManager()
{
  ImageManager imageManager = ImageManager::GetInstance();
  sf::Image& baseGUI = imageManager.GetImage( "GUIA.png" );
  fBaseWidth = baseGUI.GetWidth();
  fBaseHeight = baseGUI.GetHeight();
  const int pixels = fBaseWidth * fBaseHeight * 4;
  fBasePixels = new sf::Uint8[ pixels ];
  memcpy( fBasePixels, baseGUI.GetPixelsPtr(), sizeof( sf::Uint8 ) * pixels );

  if( fSubRectMap.empty() )
    {
      fSubRectMap[eBarLeft] = sf::Rect<int>( 0, 0, 20, 20 );
      fSubRectMap[eBar] = sf::Rect<int>( 20, 0, 20, 20 );
      fSubRectMap[eBarRight] = sf::Rect<int>( 120, 0, 20, 20 );
      fSubRectMap[eDecrease] = sf::Rect<int>( 40, 0, 20, 20 );
      fSubRectMap[eIncrease] = sf::Rect<int>( 60, 0, 20, 20 );
      fSubRectMap[ePlus] = sf::Rect<int>( 80, 0, 20, 20 );
      fSubRectMap[eCross] = sf::Rect<int>( 100, 0, 20, 20 );
      fSubRectMap[eOpenBox] = sf::Rect<int>( 140, 0, 20, 20 );
      fSubRectMap[eCrossBox] = sf::Rect<int>( 160, 0, 20, 20 );
      fSubRectMap[eNewFrameLeft] = sf::Rect<int>( 0, 20, 20, 20 );
      fSubRectMap[eNewFrame] = sf::Rect<int>( 20, 20, 20, 20 );
      fSubRectMap[eNewFrameRight] = sf::Rect<int>( 40, 20, 20, 20 );
    }
}

void
GUIImageManager::Initialise()
{
  Clear();
  // Use default Colour palette
  GUIDefaultPalette palette;
  for( std::map< EGUIImage, sf::Rect<int> >::iterator iTer = fSubRectMap.begin(); iTer != fSubRectMap.end(); iTer++ )
    {
      (fImages[iTer->first])[eBase] = Colourise( &palette, eBase, iTer->second, NULL );
      (fImages[iTer->first])[eHighlight] = Colourise( &palette, eHighlight, iTer->second, NULL );
      (fImages[iTer->first])[eActive] = Colourise( &palette, eActive, iTer->second, NULL );
    }
}

GUIImageManager::~GUIImageManager()
{
  Clear();
  delete fBasePixels;
}

void
GUIImageManager::Clear()
{
  for( GUIImageMap::iterator iTer = fImages.begin(); iTer != fImages.end(); iTer++ )
    {
      for( std::map< EGUIImageState, sf::Image* >::iterator iTer2 = iTer->second.begin(); iTer2 != iTer->second.end(); iTer2++ )
	delete iTer2->second;
      iTer->second.clear();
    }
    fImages.clear(); 
}

Sprite 
GUIImageManager::NewSprite( const EGUIImage image,
			    const EGUIImageState state )
{
  Sprite sprite;
  sprite.SetImage( *((fImages[image])[state]) );
  return sprite;
}

void 
GUIImageManager::ChangeColourScheme( GUIColourPalette* palette )
{
  for( std::map< EGUIImage, sf::Rect<int> >::iterator iTer = fSubRectMap.begin(); iTer != fSubRectMap.end(); iTer++ )
    {
      (fImages[iTer->first])[eBase] = Colourise( palette, eBase, iTer->second, (fImages[iTer->first])[eBase] );
      (fImages[iTer->first])[eHighlight] = Colourise( palette, eHighlight, iTer->second, (fImages[iTer->first])[eHighlight] );
      (fImages[iTer->first])[eActive] = Colourise( palette, eActive, iTer->second, (fImages[iTer->first])[eActive] );
    }
}

sf::Image*
GUIImageManager::Colourise( GUIColourPalette* palette,
			    EGUIImageState state,
			    sf::Rect<int> sourceRect,
			    sf::Image* colouredImage )
{
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

  if( colouredImage == NULL )
    colouredImage = new sf::Image();
  colouredImage->LoadFromPixels( sourceRect.Width, sourceRect.Height, pixels );
  delete pixels;
  return colouredImage;
}
