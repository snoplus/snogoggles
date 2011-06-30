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

namespace Viewer
{
namespace GUIs
{

class Button : public GUI
{
public:
  inline Button( sf::Rect<double>& rect, unsigned int guiID );
  virtual ~Button() {};
  virtual void Render( sf::RenderWindow& windowApp, const FrameCoord& frameCoord ) = 0;
  virtual UIEvent NewEvent( sf::Event& event );

  inline virtual bool GetState();
protected:
  bool fPressed;
};

Button::Button( sf::Rect<double>& rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false; 
}

bool
Button::GetState()
{
  return fPressed;
}

} // ::GUIs

} // ::Viewer

#endif
