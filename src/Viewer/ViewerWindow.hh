////////////////////////////////////////////////////////////////////////
/// \class Viewer::ViewerWindow
///
/// \brief   The Singleton class that is the SNOGoggles Viewer
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///     06/07/11 : Olivia Wasalski - Added the SetGlobalGLStates method. \n
///     07/08/11 : P.Jones - Added global palette factories. \n
///
/// \detail  As Brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ViewerWindow__
#define __Viewer_ViewerWindow__

#include <cstddef> //NULL and other things

#include <Viewer/FrameManager.hh>
#include <Viewer/ColourPaletteFactory.hh>
#include <Viewer/GUIColourPaletteFactory.hh>

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

  static ColourPaletteFactory gColourPaletteFactory;
  static GUIColourPaletteFactory gGUIColourPaletteFactory;


  void Initialise();
  
  void Run();

  void Destruct();

private:
  ViewerWindow();

  void DrawSplash();

  void EventLoop();

  void RenderLoop();

  /// Resets OpenGL's depth and stencil buffers.
  void SetGlobalGLStates();

  FrameManager fFrameManager;
  sf::RenderWindow* fWindowApp;
  
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
