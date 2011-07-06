#include <SFML/Window/Event.hpp>

#include <Viewer/Persist.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
Persist::NewEvent( UIEvent& event )
{
  switch( event.Type )
    {
     case sf::Event::MouseButtonReleased:
      fActive = !fActive;
      break;
    }
  return GUIReturn( fID, fGlobalID );
}
