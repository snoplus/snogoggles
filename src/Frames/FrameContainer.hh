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

namespace sf
{
  class RenderWindow;
  class Event;
}

namespace Viewer
{
  class ConfigurationTable;
  class Frame;

  //namespace GUI
  //{
  //  class Button;
  //  class DragAble;
  //}

class FrameContainer
{
public:
  void Initialise( ConfigurationTable& configTable );
  
  void Render2d( sf::RenderWindow& windowApp );
  void Render3d( sf::RenderWindow& windowApp );
  void RenderGUI( sf::RenderWindow& windowApp );

  void NewEvent( sf::Event& event );
  
  void SaveConfiguration( ConfigurationTable& configTable );

  void SetContainerCoord( FrameCoord& frameCoord );
private:
  FrameCoord fContainerCoord;
  
  Frame* fFrame;
  //GUI::Button* fPinButton;
  //GUI::Button* fExitButton;
  //GUI::DragAble* fTopBar;
};

} // ::Viewer

#endif
