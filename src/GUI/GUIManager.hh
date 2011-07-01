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
#include <SFML/System/Vector2.hpp>

#include <vector>

#include <Viewer/GUIReturn.hh>

namespace Viewer
{
  class GUI;
  class FrameCoord;
  class UIEvent;
  class RWWrapper;

class GUIManager
{
public:
  GUIReturn NewEvent( UIEvent& event );
  void Render( RWWrapper& windowApp );
  
  template<class T> inline
  GUI* NewGUI( sf::Rect<double>& rect );

  GUI* GetGUI( unsigned int guiID );
private:
  int FindGUI( sf::Vector2<double> localCoord );

  std::vector<GUI*> fGUIObjects;
  int fFocus;
};

template<class T>
GUI* 
GUIManager::NewGUI( sf::Rect<double>& rect )
{
  GUI* gui = new T( rect, fGUIObjects.size() );
  fGUIObjects.push_back( gui );
  return gui;
}

} // ::Viewer

#endif
