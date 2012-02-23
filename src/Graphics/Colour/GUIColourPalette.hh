////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIColourPalette
///
/// \brief   Colour palette for GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail Defines the colours for GUI objects 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIColourPalette__
#define __Viewer_GUIColourPalette__

#include <Viewer/Colour.hh>

namespace Viewer
{
  enum EGUITextureState { eBase, eHighlight, eActive };

class GUIColourPalette
{
public:
  virtual Colour GetBaseColour( EGUITextureState state ) = 0;
  virtual Colour GetBGColour( EGUITextureState state ) = 0;
  virtual Colour GetItemColour( EGUITextureState state ) = 0;
  virtual Colour GetTextColour( EGUITextureState state ) = 0;
  
  virtual std::string GetName() = 0;
  
  static GUIColourPalette* gPalette;
};

} // ::Viewer

#endif
