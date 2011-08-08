////////////////////////////////////////////////////////////////////////
/// \class Viewer::GreyScalePalette
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

#ifndef __Viewer_GreyScalePalette__
#define __Viewer_GreyScalePalette__

#include <Viewer/ColourPalette.hh>

namespace Viewer
{

class GreyScalePalette : public ColourPalette
{
public:
  virtual Colour GetColour( double value );
  virtual Colour GetPrimaryColour( EColour value );

  std::string GetName() { return GreyScalePalette::Name(); }
  static std::string Name() { return std::string("Grey Scale"); }
};

} // ::Viewer

#endif
