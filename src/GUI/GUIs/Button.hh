////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::Button
///
/// \brief   Button GUI objects
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     29/06/11 : P.Jones - First Revision, new file. \n
///     05/06/12 : P.Jones - Second Revision, No longer base class.\n
///
/// \detail  Button (release to change state, state change on loss focus).
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_Button__
#define __Viewer_GUIs_Button__

#include <Viewer/GUI.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
namespace GUIs
{

class Button : public GUI
{
public:
  inline Button( RectPtr rect, 
                 unsigned int guiID );
  virtual ~Button();
  virtual void Initialise( unsigned int textureNumber );
  
  virtual void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  inline bool GetState() const;
protected:
  sf::Texture* fButton[3]; /// < The button textures, base, highlight, active

  bool fPressed; /// < Is button pressed?
  bool fHover; /// < Is button hovered?
};

Button::Button( RectPtr rect, unsigned int guiID ) 
  : GUI( rect, guiID ) 
{ 
  fPressed = false; 
  fHover = false;
}

bool
Button::GetState() const
{
  return fPressed;
}

} // ::GUIs

} // ::Viewer

#endif
