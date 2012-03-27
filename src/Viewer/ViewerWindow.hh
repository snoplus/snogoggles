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
///     18/02/12 : P.Jones - New overall structure refactor. \n
///
/// \detail  As Brief, note this is only the drawable aspects of the 
///          viewer.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_ViewerWindow__
#define __Viewer_ViewerWindow__

#include <cstddef> //NULL and other things

#include <Viewer/ColourPaletteFactory.hh>
#include <Viewer/GUIColourPaletteFactory.hh>

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{
  class Rect;
  class DesktopManager;

class ViewerWindow
{
public:
  static ColourPaletteFactory gColourPaletteFactory;
  static GUIColourPaletteFactory gGUIColourPaletteFactory;
  /// Destructor
  ~ViewerWindow();
  /// Singleton accessor 
  inline static ViewerWindow& GetInstance();
  /// Initialise all the singletons
  void InitAll();
  /// Start the viewer, load settings etc...
  void Initialise();
  /// Run loop, polled by the thread
  void Run();
  /// Destroy the viewer, saving settings
  void Destruct();
private:
  /// Initialise this window
  ViewerWindow();
  /// Draw a splash whilst loading the viewer
  void DrawSplash();
  /// Deal with any UI events
  bool EventLoop();
  /// Draw stuff to the screen
  void RenderLoop();
  /// Resets OpenGL's depth and stencil buffers.
  void SetGlobalGLStates();
  /// Prevent these from being called, as singleton
  ViewerWindow( ViewerWindow const& );
  void operator=( ViewerWindow const& );

  DesktopManager* fDesktopManager; /// < Manages which desktop is shown
  Rect* fMotherRect; /// < The global mother rect
  sf::RenderWindow* fWindowApp; /// < The sfml window to draw on
};

inline ViewerWindow&
ViewerWindow::GetInstance()
{
  static ViewerWindow viewer;
  return viewer;
}

} //::Viewer

#endif
