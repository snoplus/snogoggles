////////////////////////////////////////////////////////////////////////
/// \class Viewer::GUIs::TextBox
///
/// \brief   TextBox GUI objects
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     10/08/12 : P.Jones - First Revision, new file. \n
///
/// \detail  TextBox can type text into it.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_GUIs_TextBox__
#define __Viewer_GUIs_TextBox__

#include <SFML/System/String.hpp>
#include <SFML/System/Clock.hpp>

#include <sstream>

#include <Viewer/GUI.hh>
#include <Viewer/Text.hh>

namespace sf
{
  class Texture;
}

namespace Viewer
{
namespace GUIs
{

class TextBox : public GUI
{
public:
  TextBox( RectPtr rect, 
           unsigned int guiID );
  virtual ~TextBox();
  
  virtual void Render( RWWrapper& renderApp );
  GUIEvent NewEvent( const Event& event );

  std::string GetString() const { return fText; }

protected:
  void RightCursor();
  void LeftCursor();

  sf::String fText; /// < The entered text (unicode)
  sf::Clock fClock; /// < Blinking cursor timer
  Text* fDrawnText; /// < The drawn text
  sf::Texture* fLeftBox[3]; /// < The textBox textures, base, highlight, active
  sf::Texture* fMiddleBox[3]; /// < The textBox textures, base, highlight, active
  sf::Texture* fRightBox[3]; /// < The textBox textures, base, highlight, active
  sf::Texture* fCursor[3]; /// < The cursor textures, base, highlight, active
  int fCursorPos; /// < Position of the cursor

  bool fBlink; /// < Visible or invisible cursor (true is visible)
  bool fActive; /// < Has focus?
  bool fHover; /// < Hovering over?
};

} // ::GUIs

} // ::Viewer

#endif
