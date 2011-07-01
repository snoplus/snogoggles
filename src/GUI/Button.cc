#include <SFML/Window/Event.hpp>

#include <Viewer/Button.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
Button::NewEvent( UIEvent& event )
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
  return GUIReturn( fID, fGlobalID );
}
