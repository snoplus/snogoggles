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

#include <SFML/System/Clock.hpp>

#include <vector>

#include <Viewer/Frame.hh>

namespace Viewer
{
  class FrameManager;
namespace GUIs
{
  class NewFrameButton;
}

namespace Frames
{

class MasterUI : public Frame
{
public:
  MasterUI( FrameManager* manager );

  void Initialise() { };

  void NewEvent( UIEvent& event );

  virtual void EventLoop();
  
  virtual std::string GetName() { return MasterUI::Name(); }
  
  static std::string Name() { return std::string( "MasterUI" ); }

  virtual void Render2d( RWWrapper& windowApp ) { };

  void Render3d() { }

private:
  void HideAllButtons();
  void MoveButtons();
  void PositionButtons( const double height );

  enum EState { eDown, eRising, eFalling, eUp };

  EState fCurrentState;
  EFrameType fFrameInterest;
  sf::Clock fClock;

  FrameManager* fFrameManager;

  GUIs::NewFrameButton* fUtilButton;
  GUIs::NewFrameButton* f2dButton;
  GUIs::NewFrameButton* f3dButton;
  std::vector<GUIs::NewFrameButton*> fUtilButtons;
  std::vector<GUIs::NewFrameButton*> f2dButtons;
  std::vector<GUIs::NewFrameButton*> f3dButtons;
  std::map<int, std::string> fFrameNameMap; /// < Map guiID to frame name
};

} // ::Frames

} // ::Viewer

#endif
