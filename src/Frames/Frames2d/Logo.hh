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

#include <Viewer/Frame2d.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{
namespace Frames
{

class Logo : public Frame2d
{
public:
  void Initialise( ConfigurationTable& configTable );

  void SaveConfiguration( ConfigurationTable& configTable );

  virtual void EventLoop();
  
  virtual std::string GetName() { return Logo::Name(); }
  
  static std::string Name() { return std::string( "Logo" ); }

  virtual void Render2d( RWWrapper& windowApp );
private:
  Sprite fLogo;
  Sprite fLogo2;
  bool fState;
};

} // ::Frames

} // ::Viewer

#endif
