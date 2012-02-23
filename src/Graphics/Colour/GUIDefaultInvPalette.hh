////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIDefaultInvPalette
///
/// \brief   Default colour palette for GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     07/08/11 : P.Jones - First Revision, new file. \n
///
/// \detail As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIDefaultInvPalette__
#define __Viewer_GUIDefaultInvPalette__

#include <Viewer/GUIColourPalette.hh>

namespace Viewer
{

class GUIDefaultInvPalette : public GUIColourPalette
{
public:
  Colour GetBaseColour( EGUITextureState state );
  Colour GetBGColour( EGUITextureState state );
  Colour GetItemColour( EGUITextureState state );
  Colour GetTextColour( EGUITextureState state );

  std::string GetName() { return Name(); }
  static std::string Name() { return std::string("Default Inverted"); }
};

} // ::Viewer

#endif
