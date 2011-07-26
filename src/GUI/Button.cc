#include <SFML/Window/Event.hpp>

#include <Viewer/Button.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
Button::NewEvent( UIEvent& event )
{
  GUIReturn retEvent;
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      fPressed = true;
      break;
    case sf::Event::MouseMoved:
      fHover = true;
      break;
    case sf::Event::MouseButtonReleased:
      retEvent = GUIReturn( fID, fGlobalID );
    case sf::Event::LostFocus:
      fPressed = false;
      fHover = false;
      break;
    }
  return retEvent;
}
