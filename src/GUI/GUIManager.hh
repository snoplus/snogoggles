////////////////////////////////////////////////////////////////////////
/// \class GUIManager
///
/// \brief   Manages the GUI objects in a frame
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIManager__
#define __Viewer_GUIManager__

#include <SFML/Graphics/Rect.hpp>

#include <vector>

#include <Viewer/UIEvent.hh>

namespace sf
{
  class Event;
  class RenderWindow;
}

namespace Viewer
{
  class GUI;

class GUIManager
{
public:
  UIEvent NewEvent( sf::Event& event );
  void Render( sf::RenderWindow& windowApp );
  
  template<class T>
  GUI* NewGUI( sf::Rect<double>& rect );

  GUI* GetGUI( unsigned int guiID );
private:
  std::vector<GUI*> fGUIObjects;
  int fFocus;
};

} // ::Viewer

#endif
