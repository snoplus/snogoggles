////////////////////////////////////////////////////////////////////////
/// \class Viewer::ColourPalette
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

#ifndef __Viewer_ColourPalette__
#define __Viewer_ColourPalette__

#include <string>

#include <Viewer/Colour.hh>

namespace Viewer
{

  enum EColour { eBlack = 0, eWhite = 1, eRed = 2, eOrange = 3, eYellow = 4, eGreen = 5, eBlue = 6, eIndigo = 7, eViolet = 8, eGrey = 9 };

class ColourPalette
{
public:
  virtual Colour GetColour( double value ) = 0;
  virtual Colour GetPrimaryColour( EColour value ) = 0;
  virtual std::string GetName() = 0;

  static ColourPalette* gPalette;
};

} // ::Viewer

#endif
