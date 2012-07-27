#include <SFML/Window/Event.hpp>

#include <Viewer/Button.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

void
Button::Initialise( unsigned int textureNumber )
{
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fButton[0] = textureManager.GetTexture( textureNumber, eBase );
  fButton[1] = textureManager.GetTexture( textureNumber, eHighlight );
  fButton[2] = textureManager.GetTexture( textureNumber, eActive );
}

Button::~Button()
{
  fButton[0] = NULL; // Manager deletes the texture
  fButton[1] = NULL; // Manager deletes the texture
  fButton[2] = NULL; // Manager deletes the texture
}

GUIEvent 
Button::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  switch( event.type )
    {
    case sf::Event::MouseButtonPressed:
      fPressed = true;
      break;
    case sf::Event::MouseMoved:
      fHover = true;
      break;
    case sf::Event::MouseButtonReleased:
      retEvent = GUIEvent( fID, fGlobalID );
      fPressed = false;
      fHover = false;
      break;
    case sf::Event::LostFocus:
      if( fPressed )
        retEvent = GUIEvent( fID, fGlobalID );
      fPressed = false;
      fHover = false;
      break;
    }
  return retEvent;
}

void
Button::Render( RWWrapper& renderApp )
{
  Sprite buttonSprite( fRect );

  if( !fPressed && !fHover )
    buttonSprite.SetTexture( fButton[0] );
  else if( fHover )
    buttonSprite.SetTexture( fButton[1] );
  else
    buttonSprite.SetTexture( fButton[2] );
  renderApp.Draw( buttonSprite );
}
