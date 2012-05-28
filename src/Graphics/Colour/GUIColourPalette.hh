////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIColourPalette
///
/// \brief   Colour palette for GUI objects
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///     25/05/12 : P.Jones - Second Revision, now loads from an xml file.\n
///
/// \detail Defines the colours for GUI objects 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIColourPalette__
#define __Viewer_GUIColourPalette__

#include <string>
#include <map>

#include <Viewer/Colour.hh>
#include <Viewer/GUI.hh>

namespace Viewer
{

class GUIColourPalette
{
public:
  GUIColourPalette();
  ~GUIColourPalette();
  /// Load the colour palette from a xml file
  void Load( const std::string& fileName );
  /// Get the background colour, no states here
  Colour GetBackground() const;
  /// Get the colour for state
  Colour GetA( EGUIState state ) const { return fA.find(state)->second; };
  Colour GetB( EGUIState state ) const { return fB.find(state)->second; };
  Colour GetC( EGUIState state ) const { return fC.find(state)->second; };
  Colour GetD( EGUIState state ) const { return fD.find(state)->second; };
  Colour GetE( EGUIState state ) const { return fE.find(state)->second; };
  Colour GetF( EGUIState state ) const { return fF.find(state)->second; };
  /// Switch the background colour
  void SwitchBackground() { fInverted = !fInverted; };
private:
  /// The comment refers to suggested usage, the code and images define the actual usage.
  Colour fBackground; /// < Background colour
  Colour fInvBackground; /// < Inverted background colour
  bool fInverted; /// < Invert the background colour
  std::map< EGUIState, Colour > fA; /// < This is the effective fill colour
  std::map< EGUIState, Colour > fB; /// < This is the effective accent colour (text)
  std::map< EGUIState, Colour > fC; /// < This is the effective border colour
  std::map< EGUIState, Colour > fD; /// < Fill shadow colour
  std::map< EGUIState, Colour > fE; /// < Accent shadow colour 
  std::map< EGUIState, Colour > fF; /// < Border shadow colour
};

} // ::Viewer

#endif
