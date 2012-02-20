////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Button
///
/// \brief   A Base class for button GUI objects
///
/// \author  Phil Jones <p.jones22@physics.ox.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///
/// \detail  As brief
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Button__
#define __Viewer_GUIs_Button__

#include <Viewer/GUI.hh>
#include <Viewer/RectPtr.hh>

namespace Viewer
{
  class Event;
namespace GUIs
{

class Button : public GUI
{
public:
  inline Button( RectPtr rect, unsigned int guiID );
  virtual ~Button() {};
 
  virtual void Render( RWWrapper& renderApp ) = 0;
  virtual GUIEvent NewEvent( Event& event );

  inline virtual bool GetState();
protected:
  bool fPressed;
  bool fHover;
};

Button::Button( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false; 
  fHover = false;
}

bool
Button::GetState()
{
  return fPressed;
}

} // ::GUIs

} // ::Viewer

#endif
