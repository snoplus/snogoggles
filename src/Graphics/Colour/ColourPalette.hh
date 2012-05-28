////////////////////////////////////////////////////////////////////////
/// \class Viewer::ColourPalette
///
/// \brief   The viewer colour palette
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     11/07/11 : P.Jones - First Revision, new file. \n
///     28/05/12 : P.Jones - Second Revision, refactor now loaded.\n
///
/// \detail  Colour palettes are loaded from xml files and accessed via
///          this class. 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ColourPalette__
#define __Viewer_ColourPalette__

#include <string>
#include <map>
#include <vector>

#include <Viewer/Colour.hh>

namespace Viewer
{

enum EColour { eBlack = 0, eWhite = 1, eRed = 2, eOrange = 3, eYellow = 4, eGreen = 5, eBlue = 6, eIndigo = 7, eViolet = 8, eGrey = 9 };

class ColourPalette
{
public:
  enum EScalingMode { eContinuous, eDiscrete };
  /// Load a colour palette given a fileName
  void LoadColourPalette( const std::string& fileName );
  /// Get the colour given a value [0,1]
  Colour GetColour( double value );
  /// Get a primary colour
  inline Colour GetPrimaryColour( EColour value );
  /// Get the current palette name
  //std::string GetName();
  static ColourPalette gPalette;
private:
  std::map<EColour, Colour> fPrimaryColours; /// < The primary colours mapping
  std::vector< std::pair< double, Colour > > fColourStops; /// < The colour stop values and colours, in order
  EScalingMode fMode;
};

inline Colour 
ColourPalette::GetPrimaryColour( EColour value )
{
  return fPrimaryColours[value];
}

} // ::Viewer

#endif
