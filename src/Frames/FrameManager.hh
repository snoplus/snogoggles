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

#include <vector>

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace Viewer
{
  class ConfigurationTable;
  class FrameContainer;

class FrameManager
{
public:
  void Initialise( ConfigurationTable& configTable );
  
  void NewEvent( sf::Event& event );
  void RenderGUI( sf::RenderWindow& windowApp );
  void Render2d( sf::RenderWindow& windowApp );
  void Render3d( sf::RenderWindow& windowApp );
  
  void SaveConfiguration( ConfigurationTable& configTable );
private:
  std::vector<FrameContainer*> fFrames;
  int fFocus;
};

} // ::Viewer

#endif
