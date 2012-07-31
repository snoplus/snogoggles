#include <SFML/Window/Event.hpp>

#include <Viewer/MapArea.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIEvent 
MapArea::NewEvent( const Event& event )
{
  GUIEvent ret; // NULL event
  switch( event.type )
    {
    case sf::Event::MouseMoved:
      {
        sf::Vector2<double> resPos = event.GetPos();
        sf::Rect<double> resRect = fRect->GetRect( Rect::eResolution );
        fCurrentPos = sf::Vector2<double>( ( resPos.x - resRect.left ) / resRect.width, ( resPos.y - resRect.top ) / resRect.height );
        ret = GUIEvent( fID, fGlobalID );
        break;
      }
    case sf::Event::LostFocus:
      fCurrentPos = sf::Vector2<double>( -1, -1 );
      ret = GUIEvent( fID, fGlobalID );
      break;
    }
  return ret;
}
