////////////////////////////////////////////////////////////////////////
/// \class Viewer::RainbowPalette
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

#ifndef __Viewer_RainbowPalette__
#define __Viewer_RainbowPalette__

#include <Viewer/ColourPalette.hh>

namespace Viewer
{

class RainbowPalette : public ColourPalette
{
public:
  virtual Colour GetColour( double value );
  virtual Colour GetPrimaryColour( EColour value );

  std::string GetName() { return RainbowPalette::Name(); }
  static std::string Name() { return std::string( "Rainbow" ); }
};

} // ::Viewer

#endif
