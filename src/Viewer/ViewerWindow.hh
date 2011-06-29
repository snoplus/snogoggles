////////////////////////////////////////////////////////////////////////
/// \class Viewer::ViewerWindow
///
/// \brief   The Singleton class that is the SNOGoggles Viewer
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As Brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ViewerWindow__
#define __Viewer_ViewerWindow__

#include <cstddef> //NULL and other things

#include <Viewer/FrameManager.hh>

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{

class ViewerWindow
{
public:
  inline static ViewerWindow& GetInstance();

  void Initialise();
  
  void Run();

  void Destruct();

private:
  ViewerWindow();

  void EventLoop();

  void RenderLoop();

  FrameManager fFrameManager;
  sf::RenderWindow* fWindowApp;
  //Configuration fConfiugration;
  
  static ViewerWindow* fViewer;
};

ViewerWindow&
ViewerWindow::GetInstance()
{
  if( fViewer == NULL )
    fViewer = new ViewerWindow();
  return *fViewer;
}

} //::Viewer

#endif
