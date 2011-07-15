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

#include <iostream>

#include <Viewer/Rect.hh>
#include <Viewer/FrameUIReturn.hh>
#include <Viewer/FrameFactory.hh>
#include <Viewer/Persist.hh>

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{
  class ConfigurationTable;
  class Frame;
  class GUI;
  class UIEvent;
namespace GUIs
{
  class Button;
  class Persist;
}

class FrameContainer
{
public:
  FrameContainer();
  virtual ~FrameContainer();

  void Initialise( const std::string& type );
  void LoadConfiguration( ConfigurationTable& configTable );

  void EventLoop();  
  void Render2d( sf::RenderWindow& windowApp );
  void Render3d();
  void RenderGUI( sf::RenderWindow& windowApp );

  FrameUIReturn NewEvent( UIEvent& event );
  void SaveConfiguration( ConfigurationTable& configTable );

  void Resize( const sf::Vector2<double>& size );
  void Move( const sf::Vector2<double>& position );
  void SetContainerRect( Rect& fContainerRect );
  Rect GetContainerRect();
  sf::Vector2<double> GetPos();
  sf::Vector2<double> GetSize();

  inline bool IsPinned();
private:
  Rect fContainerRect;
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
