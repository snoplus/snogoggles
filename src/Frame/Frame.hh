////////////////////////////////////////////////////////////////////////
/// \class Frame
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

#include <FrameCoord.hh>
#include <GUIManager.hh>

namespace Viewer
{

class Frame
{
public:
  void RenderGUI( sf::RenderWindow& windowApp );

  void NewEvent( sf::Event& event );
  
  void Initialise( ConfigurationTable& configTable );

  virtual void EventLoop() = 0;
  
  virtual void GetName() = 0;

  virtual void SaveConfiguration( ConfigurationTable& configTable ) = 0;

  virtual void Render() = 0;
private:
  FrameCoord fFrameCoord;
  GUIManager fGUIManager;
  std::queue<Viewer::Event> fEvents;
};

} // ::Viewer

#endif
