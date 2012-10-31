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
  Text fDrawnText; /// < The drawn text
  sf::Texture* fTextBox[3]; /// < The textBox textures, base, highlight, active
  int fCursor; /// < Position of the cursor

  bool fActive; /// < Has focus?
  bool fHover; /// < Hovering over?
};

} // ::GUIs

} // ::Viewer

#endif
