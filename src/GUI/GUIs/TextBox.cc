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
  : GUI( rect, guiID )
{
  sf::Rect<double> size = rect->GetRect( Rect::eLocal );
  size.height = 0.8;
  size.top = 0.1;
  fDrawnText = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  fActive = false;
  fHover = false;
  fCursorPos = 0;
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fLeftBox[0] = textureManager.GetTexture( 45, eBase );
  fLeftBox[1] = textureManager.GetTexture( 45, eHighlight );
  fLeftBox[2] = textureManager.GetTexture( 45, eActive );
  fMiddleBox[0] = textureManager.GetTexture( 42, eBase );
  fMiddleBox[1] = textureManager.GetTexture( 42, eHighlight );
  fMiddleBox[2] = textureManager.GetTexture( 42, eActive );
  fRightBox[0] = textureManager.GetTexture( 46, eBase );
  fRightBox[1] = textureManager.GetTexture( 46, eHighlight );
  fRightBox[2] = textureManager.GetTexture( 46, eActive );
  fCursor[0] = textureManager.GetTexture( 43, eBase );
  fCursor[1] = textureManager.GetTexture( 43, eHighlight );
  fCursor[2] = textureManager.GetTexture( 43, eActive );
}

TextBox::~TextBox()
{
  delete fDrawnText;
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
      fsKeyboardFocus = fGlobalID;
      break;
    case sf::Event::MouseButtonReleased:
      fActive = false;
      fHover = false;
      fsKeyboardFocus = fGlobalID;
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
      if( event.text.unicode == 13 ) // Return key
        break;
      if( event.text.unicode == '\b' )
        {
          LeftCursor();
          if( !fText.isEmpty() )
            fText.erase( fCursorPos, 1 );
        }
      else if( event.text.unicode == 128 ) //Delete
        {
          if( !fText.isEmpty() )
            fText.erase( fCursorPos, 1 );
          LeftCursor();
        }
      else if( event.text.unicode < 123 )
        {
          fText.insert( fCursorPos, event.text.unicode );
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
        case sf::Keyboard::Return:
          retEvent = GUIEvent( fID, fGlobalID );
          break;
        }
        break;
    }
      
  return retEvent;
}

void
TextBox::LeftCursor()
{
  fCursorPos--;
  if( fCursorPos < 0 )
    fCursorPos = 0;
}

void
TextBox::RightCursor()
{
  fCursorPos++;
  if( fCursorPos > fText.getSize() )
    fCursorPos--;
}

void
TextBox::Render( RWWrapper& renderApp )
{
  sf::Rect<double> size = fRect->GetRect( Rect::eResolution );
  size.width = 20.0;
  Sprite left( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size.top += 2.0;
  size.height -= 4.0;
  Sprite cursor( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size = fRect->GetRect( Rect::eResolution );
  size.left += 20.0;
  size.width -= 40.0;
  Sprite middle( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size = fRect->GetRect( Rect::eResolution );
  size.left = size.left + size.width - 20.0;
  size.width = 20.0;
  Sprite right( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );

  if( !fActive && !fHover )
    {
      left.SetTexture( fLeftBox[0] );
      middle.SetTexture( fMiddleBox[0] );
      right.SetTexture( fRightBox[0] );
      cursor.SetTexture( fCursor[0] );
    }
  else if( fHover )
    {
      left.SetTexture( fLeftBox[1] );
      middle.SetTexture( fMiddleBox[1] );
      right.SetTexture( fRightBox[1] );
      cursor.SetTexture( fCursor[1] );
    }
  else
    {
      left.SetTexture( fLeftBox[2] );
      middle.SetTexture( fMiddleBox[2] );
      right.SetTexture( fRightBox[2] );
      cursor.SetTexture( fCursor[2] );
    }
  renderApp.Draw( left );
  renderApp.Draw( middle );
  renderApp.Draw( right );
  fDrawnText->SetString( fText.toAnsiString() );
  if( fClock.getElapsedTime().asSeconds() > 0.5 )
    {
      fClock.restart();
      fBlink = !fBlink;
    }
  if( fText.isEmpty() && fBlink )
    renderApp.Draw( cursor );
  renderApp.Draw( *fDrawnText );
}
