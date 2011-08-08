#include <Viewer/ColourPaletteFactory.hh>
#include <Viewer/GreyScalePalette.hh>
#include <Viewer/RainbowPalette.hh>
#include <Viewer/RainbowDiscretePalette.hh>
using namespace Viewer;

#include <string>
using namespace std;

ColourPaletteFactory::ColourPaletteFactory()
{
  Register( GreyScalePalette::Name(), new Alloc<ColourPalette, GreyScalePalette>() );
  Register( RainbowPalette::Name(), new Alloc<ColourPalette, RainbowPalette>() );
  Register( RainbowDiscretePalette::Name(), new Alloc<ColourPalette, RainbowDiscretePalette>() );
}
