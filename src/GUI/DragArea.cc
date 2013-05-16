#include <SFML/Window/Event.hpp>

#include <Viewer/DragArea.hh>
#include <Viewer/Event.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIEvent 
DragArea::NewEvent( const Event& event )
{
  GUIEvent retEvent  = GUIEvent( fID, fGlobalID );
  switch( event.type )
    {
    case sf::Event::MouseButtonPressed:
      fStartPos = event.GetPos();
      fCurrentPos = event.GetPos();
      if( event.mouseButton.button == sf::Mouse::Left )
        fLeftPressed = true;
      else if( event.mouseButton.button == sf::Mouse::Right )
        fRightPressed = true;
      break;
    case sf::Event::MouseMoved:
      if( fLeftPressed || fRightPressed )
        fCurrentPos = event.GetPos();
      break;
    case sf::Event::MouseButtonReleased:
    case sf::Event::LostFocus:
      fLeftPressed = false;
      fRightPressed = false;
      fStartPos = fCurrentPos = sf::Vector2<double>( -1, -1 );
      break;
    }
  return retEvent;
}
