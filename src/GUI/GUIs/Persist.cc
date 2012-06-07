#include <SFML/Window/Event.hpp>

#include <Viewer/Persist.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

void
Persist::Initialise( unsigned int textureNumber )
{
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fPersistOff[0] = textureManager.GetTexture( textureNumber, eBase );
  fPersistOff[1] = textureManager.GetTexture( textureNumber, eHighlight );
  fPersistOff[2] = textureManager.GetTexture( textureNumber, eActive );
  fPersistOn[0] = textureManager.GetTexture( textureNumber + 1, eBase );
  fPersistOn[1] = textureManager.GetTexture( textureNumber + 1, eHighlight );
  fPersistOn[2] = textureManager.GetTexture( textureNumber + 1, eActive );
}

Persist::~Persist()
{
  fPersistOff[0] = NULL; // Manager deletes the texture
  fPersistOff[1] = NULL; // Manager deletes the texture
  fPersistOff[2] = NULL; // Manager deletes the texture
  fPersistOn[0] = NULL; // Manager deletes the texture
  fPersistOn[1] = NULL; // Manager deletes the texture
  fPersistOn[2] = NULL; // Manager deletes the texture
}

GUIEvent 
Persist::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      fPressed = true;
      fOn = !fOn; // Change state
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
Persist::Render( RWWrapper& renderApp )
{
  Sprite buttonSprite( fRect );

  if( fOn )
    {
      if( !fPressed && !fHover )
        buttonSprite.SetTexture( fPersistOn[0] );
      else if( fHover )
        buttonSprite.SetTexture( fPersistOn[1] );
      else
        buttonSprite.SetTexture( fPersistOn[2] );
    }
  else
    {
      if( !fPressed && !fHover )
        buttonSprite.SetTexture( fPersistOff[0] );
      else if( fHover )
        buttonSprite.SetTexture( fPersistOff[1] );
      else
        buttonSprite.SetTexture( fPersistOff[2] );
    }
  renderApp.Draw( buttonSprite );
}
