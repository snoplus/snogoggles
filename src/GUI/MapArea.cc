#include <SFML/Window/Event.hpp>

#include <Viewer/MapArea.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIEvent 
MapArea::NewEvent( Event& event )
{
  GUIEvent ret; // NULL event
  switch( event.Type )
    {
    case sf::Event::MouseMoved:
      {
	sf::Vector2<double> resPos = event.GetPos();
	sf::Rect<double> resRect = fRect->GetRect( Rect::eResolution );
	fCurrentPos = sf::Vector2<double>( ( resPos.x - resRect.Left ) / resRect.Width, ( resPos.y - resRect.Top ) / resRect.Height );
	ret = GUIEvent( fID, fGlobalID );
	break;
      }
    case sf::Event::LostFocus:
      fCurrentPos = sf::Vector2<double>( -1, -1 );
      break;
    }
  return ret;
}
