////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::EventUI
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

#ifndef __Viewer_Frames_EventUI__
#define __Viewer_Frames_EventUI__

#include <SFML/System/Clock.hpp>

#include <Viewer/Frame.hh>
#include <Viewer/Text.hh>

namespace Viewer
{
namespace GUIs
{
  class GUIImageButton;
  class CheckBoxLabel;
}

namespace Frames
{

class EventUI : public Frame
{
public:
  void Initialise();
 
  virtual void EventLoop();
  
  virtual std::string GetName() { return EventUI::Name(); }
  
  static std::string Name() { return std::string( "Event Control" ); }

  virtual void Render2d( RWWrapper& windowApp );

  void Render3d() { }

private:
  sf::Clock fClock;
  Text fEVInfoText;
  Text fMCInfoText;
  int fEVID;
  int fEVCount;
  int fMCID;
  int fMCCount;

  GUIs::GUIImageButton* fNextButton;
  GUIs::GUIImageButton* fPrevButton;
  GUIs::CheckBoxLabel* fContinuous;
};

} // ::Frames

} // ::Viewer

#endif
