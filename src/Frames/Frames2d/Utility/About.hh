////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::About
///
/// \brief   About frame, displays viewer information
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     19/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_About__
#define __Viewer_Frames_About__

#include <Viewer/Frame.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
namespace GUIs
{
  class Button;
}

namespace Frames
{

class About : public Frame
{
public:
  void Initialise();
 
  virtual void EventLoop();
  
  virtual std::string GetName() { return About::Name(); }
  
  static std::string Name() { return std::string( "About" ); }

  virtual void Render2d( RWWrapper& windowApp );

  void Render3d() { }
private:
  Text fInfoText;
};

} // ::Frames

} // ::Viewer

#endif
