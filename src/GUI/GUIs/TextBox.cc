#include <iostream>
using namespace std;

#include <SFML/Window/Event.hpp>

#include <Viewer/TextBox.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

TextBox::TextBox( RectPtr rect,
                  unsigned int guiID )
  : GUI( rect, guiID ), fDrawnText( rect )
{
  fActive = false;
  fHover = false;
  fCursor = 0;
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fTextBox[0] = textureManager.GetTexture( 22, eBase );
  fTextBox[1] = textureManager.GetTexture( 22, eHighlight );
  fTextBox[2] = textureManager.GetTexture( 22, eActive );
}

TextBox::~TextBox()
{
  fTextBox[0] = NULL; // Manager deletes the texture
  fTextBox[1] = NULL; // Manager deletes the texture
  fTextBox[2] = NULL; // Manager deletes the texture
}

GUIEvent 
TextBox::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  switch( event.type )
    {
      // Focus part
    case sf::Event::MouseButtonPressed:
      fActive = true;
      fsKeyboardFocus = fGlobalID;
      break;
    case sf::Event::MouseMoved:
      fHover = true;
      break;
    case sf::Event::MouseButtonReleased:
      retEvent = GUIEvent( fID, fGlobalID );
      fActive = false;
      fHover = false;
      break;
    case sf::Event::LostFocus:
      if( fActive )
        retEvent = GUIEvent( fID, fGlobalID );
      fActive = false;
      fHover = false;
      if( fsKeyboardFocus == fGlobalID ) // Lose the global keyboard focus
        fsKeyboardFocus = -1;
      break;
      // Text part
    case sf::Event::TextEntered:
      if( event.text.unicode == '\b' )
        {
          LeftCursor();
          if( !fText.isEmpty() )
            fText.erase( fCursor, 1 );
        }
      else if( event.text.unicode == 128 ) //Delete
        {
          if( !fText.isEmpty() )
            fText.erase( fCursor, 1 );
          LeftCursor();
        }
      else if( event.text.unicode < 123 )
        {
          fText.insert( fCursor, event.text.unicode );
          RightCursor();
        }
      break;
    case sf::Event::KeyPressed:
      switch( event.key.code )
        {
        case sf::Keyboard::Left:
          LeftCursor();
          break;
        case sf::Keyboard::Right:
          RightCursor();
          break;
        }
        break;
    }
      
  return retEvent;
}

void
TextBox::LeftCursor()
{
  fCursor--;
  if( fCursor < 0 )
    fCursor = 0;
}

void
TextBox::RightCursor()
{
  fCursor++;
  if( fCursor > fText.getSize() )
    fCursor--;
}

void
TextBox::Render( RWWrapper& renderApp )
{
  Sprite buttonSprite( fRect );

  if( !fActive && !fHover )
    buttonSprite.SetTexture( fTextBox[0] );
  else if( fHover )
    buttonSprite.SetTexture( fTextBox[1] );
  else
    buttonSprite.SetTexture( fTextBox[2] );
  renderApp.Draw( buttonSprite );
  fDrawnText.SetString( fText.toAnsiString() );
  renderApp.Draw( fDrawnText );
}
