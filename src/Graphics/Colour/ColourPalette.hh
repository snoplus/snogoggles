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
  ColourPalette();

  enum EScalingMode { eContinuous, eDiscrete };
  /// Load a colour palette given a fileName
  void Load( const std::string& fileName );
  /// Get the colour given a value [0,1]
  Colour GetColour( double value ) const ;
  /// Get a primary colour
  inline Colour GetPrimaryColour( EColour value ) const;
private:
  std::map<EColour, Colour> fPrimaryColours; /// < The primary colours mapping
  std::vector< std::pair< double, Colour > > fColourStops; /// < The colour stop values and colours, in order
  EScalingMode fMode;
};

inline Colour 
ColourPalette::GetPrimaryColour( EColour value ) const
{
  return fPrimaryColours.find(value)->second;
}

} // ::Viewer

#endif
