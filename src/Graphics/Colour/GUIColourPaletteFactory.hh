////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIColourPaletteFactory
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

#ifndef __Viewer_GUIColourPaletteFactory__
#define __Viewer_GUIColourPaletteFactory__

#include <vector>
#include <string>

#include <Viewer/Factory.hh>
#include <Viewer/GUIColourPalette.hh>

namespace Viewer
{

class GUIColourPaletteFactory : public Factory<GUIColourPalette>
{
public:   
  GUIColourPaletteFactory();
};

} // ::Viewer

#endif
