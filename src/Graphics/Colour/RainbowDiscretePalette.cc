#include <cstddef> //NULL and other things
#include <cmath>
using namespace std;

#include <Viewer/RainbowDiscretePalette.hh>
using namespace Viewer;

Colour 
RainbowDiscretePalette::GetColour( double value )
{
  const int region = value * 6;
  const int coloursPerRegion = 4;
  const double regionFraction = floor( ( value - (double) region / 6.0 ) * 6.0 * coloursPerRegion ) / (double) coloursPerRegion;
  switch( region )
    {
    case 0: //eViolet to eIndigo
      return GetPrimaryColour( eViolet ).AddColourFraction( GetPrimaryColour( eIndigo ), regionFraction );
    case 1: //eIndigo to eBlue
      return GetPrimaryColour( eIndigo ).AddColourFraction( GetPrimaryColour( eBlue ), regionFraction );
    case 2: //eBlue to eGreen
      return GetPrimaryColour( eBlue ).AddColourFraction( GetPrimaryColour( eGreen ), regionFraction );
    case 3: //eGreen to eYellow
      return GetPrimaryColour( eGreen ).AddColourFraction( GetPrimaryColour( eYellow ), regionFraction );
    case 4: //eYellow to eOrange
      return GetPrimaryColour( eYellow ).AddColourFraction( GetPrimaryColour( eOrange ), regionFraction );
    case 5: //eOrange to eRed
      return GetPrimaryColour( eOrange ).AddColourFraction( GetPrimaryColour( eRed ), regionFraction );
    case 6:
      return GetPrimaryColour( eWhite );
    }
}
  
Colour 
RainbowDiscretePalette::GetPrimaryColour( EColour value )
{
  switch( value )
    {
    case eBlack:
      return Colour( 0, 0, 0, 255 );
    case eWhite:
      return Colour( 255, 255, 255, 255 );
    case eRed:
      return Colour( 255, 0, 0, 255 );
    case eOrange:
      return Colour( 255, 127, 0, 255 );
    case eYellow:
      return Colour( 255, 255, 0, 255 );
    case eGreen:
      return Colour( 0, 255, 0, 255 );
    case eBlue:
      return Colour( 0, 0, 255, 255 );
    case eIndigo:
      return Colour( 111, 0, 255, 255 );
    case eViolet:
      return Colour( 143, 0, 255, 255 );
    case eGrey:
      return Colour( 200, 200, 200, 255 );
   }
}
