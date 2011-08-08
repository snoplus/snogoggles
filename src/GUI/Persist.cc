#include <SFML/Window/Event.hpp>

#include <Viewer/Persist.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
Persist::NewEvent( UIEvent& event )
{
  GUIReturn retEvent; // Default NULL event
  switch( event.Type )
    {
     case sf::Event::MouseButtonReleased:
      fPressed = !fPressed;
      retEvent = GUIReturn( fID, fGlobalID );
      break;
    }
  return retEvent;
}
