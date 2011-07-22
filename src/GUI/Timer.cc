#include <SFML/Window/Event.hpp>

#include <Viewer/Timer.hh>
#include <Viewer/UIEvent.hh>

namespace Viewer {
namespace GUIs {

GUIReturn Timer::NewEvent( UIEvent& event )
{
    GUIReturn retEvent;
    switch( event.Type )
        {
            case sf::Event::MouseButtonPressed:
                fPressed = true;
                fClock.Reset();
                fPreviousTime = 0;
                retEvent = GUIReturn( fID, fGlobalID );
                break;
            case sf::Event::MouseButtonReleased:
            case sf::Event::LostFocus:
                fPressed = false;
                retEvent = GUIReturn( fID, fGlobalID );
                break;
        }
    return retEvent;
}

int Timer::GetElapsedTime()
{
    if( fPressed == false )
        return -1;

    return fClock.GetElapsedTime();
}

int Timer::GetDeltaTime()
{
    if( fPressed == false )
        return -1;

    int currentTime = fClock.GetElapsedTime();
    int deltaTime = currentTime - fPreviousTime;
    fPreviousTime = currentTime;
    return deltaTime;
}

}; //  namespace GUIs
}; // namespace Viewer
