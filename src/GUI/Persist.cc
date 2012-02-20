#include <SFML/Window/Event.hpp>

#include <Viewer/Persist.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIEvent 
Persist::NewEvent( Event& event )
{
  GUIEvent retEvent; // Default NULL event
  switch( event.Type )
    {
     case sf::Event::MouseButtonReleased:
      fPressed = !fPressed;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    }
  return retEvent;
}
