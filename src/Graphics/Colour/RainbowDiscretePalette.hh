////////////////////////////////////////////////////////////////////////
/// \class Viewer::RainbowDiscretePalette
///
/// \brief   
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     11/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RainbowDiscretePalette__
#define __Viewer_RainbowDiscretePalette__

#include <Viewer/ColourPalette.hh>

namespace Viewer
{

class RainbowDiscretePalette : public ColourPalette
{
public:
  virtual Colour GetColour( double value );
  virtual Colour GetPrimaryColour( EColour value );
};

} // ::Viewer

#endif
