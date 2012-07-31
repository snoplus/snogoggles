#include <SFML/Window/Event.hpp>

#include <Viewer/DragArea.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIEvent 
DragArea::NewEvent( const Event& event )
{
  switch( event.type )
    {
    case sf::Event::MouseButtonPressed:
      fStartPos = event.GetPos();
      fPressed = true;
      break;
    case sf::Event::MouseMoved:
      if( fPressed )
	fCurrentPos = event.GetPos();
      break;
    case sf::Event::MouseButtonReleased:
    case sf::Event::LostFocus:
      fPressed = false;
      fStartPos = fCurrentPos = sf::Vector2<double>();
      break;
    }
  return GUIEvent( fID, fGlobalID );
}
