#include <SFML/Window/Event.hpp>

#include <Viewer/MapArea.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
MapArea::NewEvent( UIEvent& event )
{
  GUIReturn ret; // NULL event
  switch( event.Type )
    {
    case sf::Event::MouseMoved:
	fCurrentPos = sf::Vector2<double>( event.GetLocalCoord() );
	ret = GUIReturn( fID, fGlobalID );
      break;
    }
  return ret;
}
