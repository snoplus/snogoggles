////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::MasterUI
///
/// \brief   Simple Frame, just displays the logo
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     13/07/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_MasterUI__
#define __Viewer_Frames_MasterUI__

#include <vector>

#include <Viewer/Frame.hh>

namespace Viewer
{
  class FrameManager;
namespace GUIs
{
  class Button;
}

namespace Frames
{

class MasterUI : public Frame
{
public:
  MasterUI( FrameManager* manager );

  void Initialise() { };
  void Initialise( ConfigurationTable& configTable ) { };

  void SaveConfiguration( ConfigurationTable& configTable ) { };

  virtual void EventLoop();
  
  virtual std::string GetName() { return MasterUI::Name(); }
  
  static std::string Name() { return std::string( "MasterUI" ); }

  virtual void Render2d( RWWrapper& windowApp ) { };

  void Render3d() { }
private:
  FrameManager* fFrameManager;
  std::vector<GUIs::Button*> fButtons;
  std::vector<std::string> fFrameNames;
};

} // ::Frames

} // ::Viewer

#endif
