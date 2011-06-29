////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frame
///
/// \brief   The base class for all frames
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All Frames will derive from this, however frames should derive
///          from the 2d or 3d subclass version.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frame__
#define __Viewer_Frame__

#include <queue>
#include <string>

#include <Viewer/FrameCoord.hh>
//#include <Viewer/GUIManager.hh>
#include <Viewer/UIEvent.hh>

namespace sf
{
  class RenderWindow;
} //::sf

namespace Viewer
{
  class ConfigurationTable;

class Frame
{
public:   
  
  virtual ~Frame() {};

  virtual void RenderGUI( sf::RenderWindow& windowApp );

  virtual void NewEvent( sf::Event& event );
   
  virtual void Initialise( ConfigurationTable& configTable );

  virtual void SaveConfiguration( ConfigurationTable& configTable );

  virtual void EventLoop() = 0;
  
  virtual std::string GetName() = 0;

  virtual void Render2d( sf::RenderWindow& windowApp ) = 0;
  
  virtual void Render3d( sf::RenderWindow& windowApp ) = 0;

  inline void SetFrameCoord( const FrameCoord& frameCoord );
protected:
  FrameCoord fFrameCoord;
  //GUIManager fGUIManager;
  std::queue<UIEvent> fEvents;
};

void
Frame::SetFrameCoord( const FrameCoord& frameCoord ) 
{
  fFrameCoord = frameCoord;
}

} // ::Viewer

#endif
