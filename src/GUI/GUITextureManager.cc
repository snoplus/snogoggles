#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <sstream>
#include <string.h>
using namespace std;

#include <Viewer/GUITextureManager.hh>
#include <Viewer/Colour.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

GUITextureManager::GUITextureManager()
{

}

GUITextureManager::~GUITextureManager()
{
  ClearTextures();
}

void
GUITextureManager::ClearTextures()
{
  for( unsigned int iTexture = 0; iTexture < fTextures[eBase].size(); iTexture++ )
    {
      delete fTextures[eBase][iTexture];
      delete fTextures[eHighlight][iTexture];
      delete fTextures[eActive][iTexture];
    }
  fTextures.clear();
  if( fBasePixelsA )
    {
      delete[] fBasePixelsA;
      delete[] fBasePixelsB;
      fBasePixelsA = NULL;
    }
  fBaseWidth = 0;
  fBaseHeight = 0;
}

void
GUITextureManager::Initialise()
{
  {
    sf::Image baseImage;
    stringstream fileLocation;
    fileLocation << getenv( "VIEWERROOT" ) << "/textures/GUIA.png";
    baseImage.loadFromFile( fileLocation.str() );
    fBaseWidth = baseImage.getSize().x;
    fBaseHeight = baseImage.getSize().y;
    const int pixels = fBaseWidth * fBaseHeight * 4;
    fBasePixelsA = new sf::Uint8[ pixels ];
    memcpy( fBasePixelsA, baseImage.getPixelsPtr(), sizeof( sf::Uint8 ) * pixels );
  }
  {
    sf::Image baseImage;
    stringstream fileLocation;
    fileLocation << getenv( "VIEWERROOT" ) << "/textures/GUIB.png";
    baseImage.loadFromFile( fileLocation.str() );
    const int pixels = fBaseWidth * fBaseHeight * 4;
    fBasePixelsB = new sf::Uint8[ pixels ];
    memcpy( fBasePixelsB, baseImage.getPixelsPtr(), sizeof( sf::Uint8 ) * pixels );
  }
  const int numX = fBaseWidth / 20.0;
  const int numY = fBaseHeight / 20.0;
  for( int iX = 0; iX < numX; iX++ )
    {
      for( int iY = 0; iY < numY; iY++ )
        {
          sf::Texture* tempBase = new sf::Texture();
          tempBase->create( 20, 20 );
          fTextures[eBase].push_back( tempBase );
          sf::Texture* tempHighlight = new sf::Texture();
          tempHighlight->create( 20, 20 );
          fTextures[eHighlight].push_back( tempHighlight );
          sf::Texture* tempActive = new sf::Texture();
          tempActive->create( 20, 20 );
          fTextures[eActive].push_back( tempActive );
        }
    }
  Update();
}

sf::Texture* 
GUITextureManager::GetTexture( unsigned int textureNumber,
                               EGUIState state ) const
{
  return fTextures.find(state)->second[textureNumber];
}

void
GUITextureManager::Update()
{
  const int numX = fBaseWidth / 20.0;
  const int numY = fBaseHeight / 20.0;
  for( int iX = 0; iX < numX; iX++ )
    {
      for( int iY = 0; iY < numY; iY++ )
        {
          const int textureNumber = iX + iY * numX;
          sf::Rect<int> sourceRect( iX * 20, iY * 20, 20, 20 );
          sf::Uint8 pixels[ 20 * 20 * 4 ];
          FillPixels( pixels, sourceRect, eBase );
          fTextures[eBase][textureNumber]->update( pixels );
          FillPixels( pixels, sourceRect, eHighlight );
          fTextures[eHighlight][textureNumber]->update( pixels );
          FillPixels( pixels, sourceRect, eActive );
          fTextures[eActive][textureNumber]->update( pixels );
        }
    }
}

void 
GUITextureManager::FillPixels( sf::Uint8* pixels,
                               sf::Rect<int> sourceRect,
                               EGUIState state )
{
  for( int xPixel = 0; xPixel < sourceRect.width; xPixel++ )
    {
      for( int yPixel = 0; yPixel < sourceRect.height; yPixel++ )
        {
          const int basePixel = ( xPixel + sourceRect.left + ( yPixel + sourceRect.top ) * fBaseWidth ) * 4;
          Colour shapeColourA( fBasePixelsA[basePixel], fBasePixelsA[basePixel + 1], fBasePixelsA[basePixel + 2], fBasePixelsA[basePixel + 3] );
          Colour shapeColourB( fBasePixelsB[basePixel], fBasePixelsB[basePixel + 1], fBasePixelsB[basePixel + 2], fBasePixelsB[basePixel + 3] );
          Colour pixelColour = Colourise( shapeColourA, shapeColourB, state );
          const int pixel = ( xPixel + yPixel * sourceRect.width ) * 4;
          pixels[ pixel ] = pixelColour.r;
          pixels[ pixel + 1 ] = pixelColour.g;
          pixels[ pixel + 2 ] = pixelColour.b;
          pixels[ pixel + 3 ] = pixelColour.a;
        }
    }
}


Colour
GUITextureManager::Colourise( Colour shapeColourA,
                              Colour shapeColourB,
                              EGUIState state )
{
  Colour pixelColour;
  pixelColour = GUIProperties::GetInstance().GetGUIColourPalette().GetBackground();
  // Set the base colours
  pixelColour.AddColourFraction( GUIProperties::GetInstance().GetGUIColourPalette().GetA( state ), static_cast<double>( shapeColourA.r ) / 255.0 );
  pixelColour.AddColourFraction( GUIProperties::GetInstance().GetGUIColourPalette().GetB( state ), static_cast<double>( shapeColourA.g ) / 255.0 );
  pixelColour.AddColourFraction( GUIProperties::GetInstance().GetGUIColourPalette().GetC( state ), static_cast<double>( shapeColourA.b ) / 255.0 );
  // Now add the shadowing
  pixelColour.Tint( 1.0 + static_cast<double>( shapeColourB.r ) / 255.0 );
  pixelColour.Tint( 1.0 - static_cast<double>( shapeColourB.g ) / 255.0 );
  // Finnally set the alpha channel
  pixelColour.a = shapeColourA.a;
  return pixelColour;
}
