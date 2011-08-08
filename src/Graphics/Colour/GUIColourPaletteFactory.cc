#include <Viewer/GUIColourPaletteFactory.hh>
#include <Viewer/GUIDefaultPalette.hh>
using namespace Viewer;

#include <string>
using namespace std;

GUIColourPaletteFactory::GUIColourPaletteFactory()
{
  Register( GUIDefaultPalette::Name(), new Alloc<GUIColourPalette, GUIDefaultPalette>() );
}
