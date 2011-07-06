////////////////////////////////////////////////////////////////////////
/// \class Viewer::FrameManager
///
/// \brief   Manages the Frames' existance, position and size
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     25/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  All viewer frames are managed by this class.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_FrameManager__
#define __Viewer_FrameManager__

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace Viewer
{
  class Configuration;
  class FrameContainer;

class FrameManager
{
public:
  void Initialise( Configuration& config );
  
  void EventLoop();
  void RenderGUI( sf::RenderWindow& windowApp );
  void Render2d( sf::RenderWindow& windowApp );
  void Render3d();

  void NewEvent( sf::Event& event ); 
  void SaveConfiguration( Configuration& config );
private:
  int FindFrame( const sf::Vector2<double>& resolutionCoord );

  std::vector<FrameContainer*> fFrameContainers;
  int fFocus;
  bool fMoving;
};

} // ::Viewer

#endif
