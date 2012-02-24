#include <SFML/Window/Event.hpp>

#include <Viewer/Timer.hh>
#include <Viewer/Event.hh>

namespace Viewer {
namespace GUIs {

GUIEvent
Timer::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      fPressed = true;
      fClock.Restart();
      fPreviousTime = sf::Time();
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    case sf::Event::MouseButtonReleased:
    case sf::Event::LostFocus:
      fPressed = false;
      retEvent = GUIEvent( fID, fGlobalID );
      break;
    }
  return retEvent;
}

sf::Time
Timer::GetElapsedTime()
{
  if( fPressed == false )
    return sf::Time();
  
  return fClock.GetElapsedTime();
}

sf::Time
Timer::GetDeltaTime()
{
  if( fPressed == false )
    return sf::Time();
  
  sf::Time currentTime = fClock.GetElapsedTime();
  sf::Time deltaTime = currentTime - fPreviousTime;
  fPreviousTime = currentTime;
  return deltaTime;
}

}; //  namespace GUIs
}; // namespace Viewer
