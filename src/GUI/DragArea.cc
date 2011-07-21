#include <SFML/Window/Event.hpp>

#include <Viewer/DragArea.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIReturn 
DragArea::NewEvent( UIEvent& event )
{
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      fStartPos = sf::Vector2<double>( event.MouseButton.X, event.MouseButton.Y );
      fPressed = true;
      break;
    case sf::Event::MouseMoved:
      if( fPressed )
	fCurrentPos = sf::Vector2<double>( event.MouseMove.X, event.MouseMove.Y );
      break;
    case sf::Event::MouseButtonReleased:
    case sf::Event::LostFocus:
      fPressed = false;
      fStartPos = fCurrentPos = sf::Vector2<double>();
      break;
    }
  return GUIReturn( fID, fGlobalID );
}
