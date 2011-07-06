////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Logo
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

#ifndef __Viewer_Frames_Logo__
#define __Viewer_Frames_Logo__

#include <Viewer/Frame.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
namespace Frames
{

class Logo : public Frame
{
public:
  void Initialise( ConfigurationTable& configTable );

  void SaveConfiguration( ConfigurationTable& configTable );

  virtual void EventLoop();
  
  virtual std::string GetName() { return Logo::Name(); }
  
  static std::string Name() { return std::string( "Logo" ); }

  virtual void Render2d( RWWrapper& windowApp );

  void Render3d() { }
private:
  Sprite fLogo;
  Sprite fLogo2;
  Text fMessage;
  bool fState;
};

} // ::Frames

} // ::Viewer

#endif
