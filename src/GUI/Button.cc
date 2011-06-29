#include <SFML/Window/Event.hpp>

#include <Viewer/Button.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

UIEvent
Button::NewEvent( sf::Event& event )
{
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      fPressed = true;
      break;
    case sf::Event::MouseButtonReleased:
      fPressed = false;
      break;
    }
  return UIEvent( fID, fGlobalID );
}
