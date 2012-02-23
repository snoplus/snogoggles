#include <cstddef> //NULL and other things

#include <Viewer/GUIDefaultInvPalette.hh>
using namespace Viewer;

Colour 
GUIDefaultInvPalette::GetBaseColour( EGUITextureState state )
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
GUIDefaultInvPalette::GetBGColour( EGUITextureState state )
{
  return Colour( 0, 0, 0, 255 );
}

Colour 
GUIDefaultInvPalette::GetItemColour( EGUITextureState state )
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
GUIDefaultInvPalette::GetTextColour( EGUITextureState state )
{
  return Colour( 255, 255, 255, 255 );
}
