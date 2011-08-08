#include <cstddef> //NULL and other things

#include <Viewer/GUIDefaultInvPalette.hh>
using namespace Viewer;

Colour 
GUIDefaultInvPalette::GetBaseColour( EGUIImageState state )
{
  switch( state )
    {
    case eBase:
      return Colour( 96, 75, 216, 255 );
      break;
    case eHighlight:
      return Colour( 128, 112, 216, 255 );
      break;
    case eActive:
      return Colour( 96, 75, 216, 255 );
      break;
    }
}

Colour 
GUIDefaultInvPalette::GetBGColour( EGUIImageState state )
{
  return Colour( 0, 0, 0, 255 );
}

Colour 
GUIDefaultInvPalette::GetItemColour( EGUIImageState state )
{
  switch( state )
    {
    case eBase:
      return Colour( 255, 255, 255, 255 );
      break;
    case eHighlight:
      return Colour( 158, 0, 22, 255 );
      break;
    case eActive:
      return Colour( 255, 227, 115, 255 );
      break;
    }  
}

Colour 
GUIDefaultInvPalette::GetTextColour( EGUIImageState state )
{
  return Colour( 255, 255, 255, 255 );
}
