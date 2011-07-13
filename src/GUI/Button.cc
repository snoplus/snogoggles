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
      retEvent = GUIReturn( fID, fGlobalID );
      break;
    case sf::Event::MouseButtonReleased:
      fPressed = false;
      retEvent = GUIReturn( fID, fGlobalID );
      break;
    }
  return retEvent;
}
