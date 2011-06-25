////////////////////////////////////////////////////////////////////////
/// \class Viewer
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

#ifndef __Viewer_Viewer__
#define __Viewer_Viewer__

namespace sf
{
  class RenderWindow;
}

namespace Viewer
{

class Viewer
{
public:

  inline Viewer& GetInstance();

  void EventLoop();

  void RenderLoop();
private:
  Viewer();

  FrameManager fFrameManager;
  sf::RenderWindow* fWindowApp;
  Configuration fConfiugration;
  
  static Viewer* fViewer;
};

Viewer&
Viewer::GetInstance()
{
  if( fViewer == NULL )
    fViewer = new Viewer();
  return fViewer
}

} //::Viewer

#endif
