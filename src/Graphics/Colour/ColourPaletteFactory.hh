////////////////////////////////////////////////////////////////////////
/// \class Viewer::ColourPaletteFactory
///
/// \brief   Factory to instantiate colour palettes
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ColourPaletteFactory__
#define __Viewer_ColourPaletteFactory__

#include <vector>
#include <string>

#include <Viewer/Factory.hh>
#include <Viewer/ColourPalette.hh>

namespace Viewer
{

class ColourPaletteFactory : public Factory<ColourPalette>
{
public:   
  ColourPaletteFactory();
};

} // ::Viewer

#endif
