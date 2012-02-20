#include <SFML/Window/Event.hpp>

#include <Viewer/Button.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIEvent 
Button::NewEvent( Event& event )
{
  GUIEvent retEvent;
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      fPressed = true;
      break;
    case sf::Event::MouseMoved:
      fHover = true;
      break;
    case sf::Event::MouseButtonReleased:
      retEvent = GUIEvent( fID, fGlobalID );
    case sf::Event::LostFocus:
      fPressed = false;
      fHover = false;
      break;
    }
  return retEvent;
}
