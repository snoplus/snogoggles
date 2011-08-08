////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Timer
///
/// \brief   Base class for Timer objects.
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     21/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  Clock resets when the button is pressed. When the button
///          is not pressed, all time methods return -1.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Timer__
#define __Viewer_GUIs_Timer__

#include <Viewer/GUI.hh>
#include <SFML/System/Clock.hpp>

namespace Viewer
{
namespace GUIs
{

class Timer : public GUI
{
public:
    inline Timer( const sf::Rect<double>& rect, unsigned int guiID );
    virtual ~Timer() {};
 
    virtual void RenderT( sf::RenderWindow& windowApp ) = 0;
    virtual void Render( RWWrapper& windowApp ) = 0;
    virtual GUIReturn NewEvent( UIEvent& event );

    inline virtual bool GetState();
    int GetElapsedTime();
    int GetDeltaTime();
protected:
    sf::Clock fClock;
    int fPreviousTime;
    bool fPressed;
};

Timer::Timer( const sf::Rect<double>& rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false; 
}

bool Timer::GetState()
{
  return fPressed;
}

} // ::GUIs

} // ::Viewer

#endif
