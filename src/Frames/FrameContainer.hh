////////////////////////////////////////////////////////////////////////
/// \class FrameContainer
///
/// \brief   Collection of a Frame and top bar GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  Used in the frame manager class to manage frames. This class
///          contains the frame and the top bar GUI objects.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameContainer__
#define __Viewer_FrameContainer__

#include <Viewer/FrameCoord.hh>
#include <Viewer/FrameUIReturn.hh>
#include <Viewer/FrameFactory.hh>
#include <Viewer/Persist.hh>

namespace sf
{
  class RenderWindow;
  class Event;
}

namespace Viewer
{
  class ConfigurationTable;
  class Frame;
  class GUI;
namespace GUIs
{
  class Button;
  class Persist;
}

class FrameContainer
{
public:
  FrameContainer( ConfigurationTable& configTable );

  virtual ~FrameContainer();

  void EventLoop();  
  void Render2d( sf::RenderWindow& windowApp );
  void Render3d();
  void RenderGUI( sf::RenderWindow& windowApp );

  FrameUIReturn NewEvent( sf::Event& event );
  void SaveConfiguration( ConfigurationTable& configTable );

  void Resize( const sf::Vector2<double>& size );
  void Move( const sf::Vector2<double>& position );
  void SetContainerCoord( FrameCoord& fContainerCoord );
  FrameCoord GetContainerCoord();

  inline bool IsPinned();
private:
  FrameCoord fTopBarCoord;
  FrameFactory fFrameFactory;

  Frame* fFrame;
  GUIs::Persist* fPinButton;
  GUIs::Button* fExitButton;
  GUIs::Button* fTopBar;
};

bool
FrameContainer::IsPinned()
{
  return fPinButton->GetState();
}

} // ::Viewer

#endif
