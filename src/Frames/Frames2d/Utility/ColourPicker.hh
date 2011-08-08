////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ColourPicker
///
/// \brief   Simple Frame, just displays the logo
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ColourPicker__
#define __Viewer_Frames_ColourPicker__

#include <Viewer/Frame.hh>

namespace Viewer
{
namespace GUIs
{
  class CheckBoxLabel;
}

namespace Frames
{

class ColourPicker : public Frame
{
public:
  void Initialise();
 
  virtual void EventLoop();
  
  virtual std::string GetName() { return ColourPicker::Name(); }
  
  static std::string Name() { return std::string( "Colour Picker" ); }

  virtual void Render2d( RWWrapper& windowApp );

  void Render3d() { }
private:
  void NewColourPalette( int paletteID );
  void NewGUIColourPalette( int paletteID );

  std::vector<std::string> fColourNames;
  std::vector<std::string> fGUIColourNames;
  std::vector<GUIs::CheckBoxLabel*> fColourBoxes;
  std::vector<GUIs::CheckBoxLabel*> fGUIColourBoxes;
};

} // ::Frames

} // ::Viewer

#endif
