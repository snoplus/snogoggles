#include <SFML/Window/Event.hpp>

#include <Viewer/MapArea.hh>
#include <Viewer/UIEvent.hh>
#include <Viewer/Coord.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
MapArea::NewEvent( UIEvent& event )
{
  GUIReturn ret; // NULL event
  switch( event.Type )
    {
    case sf::Event::MouseMoved:
      {
	sf::Vector2<double> localPos = event.GetLocalCoord();
	fCurrentPos = sf::Vector2<double>( ( localPos.x - fRect.Left ) / fRect.Width, ( localPos.y - fRect.Top ) / fRect.Height );
	ret = GUIReturn( fID, fGlobalID );
	break;
      }
    case sf::Event::LostFocus:
      fCurrentPos = sf::Vector2<double>( -1, -1 );
      break;
    }
  return ret;
}
