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

#include <SFML/System/Clock.hpp>

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
namespace GUIs
{

class Timer : public GUI
{
public:
  inline Timer( RectPtr rect, unsigned int guiID );
  virtual ~Timer() {};
  
  virtual void Render( RWWrapper& windowApp ) = 0;
  virtual GUIEvent NewEvent( const Event& event );
  
  inline virtual bool GetState();
  sf::Time GetElapsedTime();
  sf::Time GetDeltaTime();
protected:
  sf::Clock fClock;
  sf::Time fPreviousTime;
  bool fPressed;
};

Timer::Timer( RectPtr rect, unsigned int guiID ) 
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
