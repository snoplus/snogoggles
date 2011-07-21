#include <cstddef> //NULL and other things

#include <Viewer/GreyScalePalette.hh>
using namespace Viewer;

ColourPalette* ColourPalette::gPalette = NULL;

Colour 
GreyScalePalette::GetColour( double value )
{
  return Colour( static_cast<sf::Uint8>( value * 16 * 16 ),
		 static_cast<sf::Uint8>( value * 16 * 16 ),
		 static_cast<sf::Uint8>( value * 16 * 16 ),
		 255 );
}
  
Colour 
GreyScalePalette::GetPrimaryColour( EColour value )
{
  switch( value )
    {
    case eBlack:
      return Colour( 0, 0, 0, 255 );
    case eWhite:
      return Colour( 255, 255, 255, 255 );
    case eRed:
      return Colour( 76, 76, 76, 255 );
    case eOrange:
      return Colour( 158, 158, 158, 255 );
    case eYellow:
      return Colour( 226, 226, 226, 255 );
    case eGreen:
      return Colour( 150, 150, 150, 255 );
    case eBlue:
      return Colour( 29, 29, 29, 255 );
    case eIndigo:
      return Colour( 37, 37, 37, 255 );
    case eViolet:
      return Colour( 47, 47, 47, 255 );
    case eGrey:
      return Colour( 200, 200, 200, 255 );
   }
}
