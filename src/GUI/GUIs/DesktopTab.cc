#include <SFML/Window/Event.hpp>

#include <Viewer/DesktopTab.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

void
DesktopTab::Initialise()
{
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  int textureNumber = 0;
  fLeftOff[0] = textureManager.GetTexture( textureNumber, eBase );
  fLeftOff[1] = textureManager.GetTexture( textureNumber, eHighlight );
  fLeftOff[2] = textureManager.GetTexture( textureNumber, eActive );
  fBaseOff[0] = textureManager.GetTexture( textureNumber + 1, eBase );
  fBaseOff[1] = textureManager.GetTexture( textureNumber + 1, eHighlight );
  fBaseOff[2] = textureManager.GetTexture( textureNumber + 1, eActive );
  fRightOff[0] = textureManager.GetTexture( textureNumber + 2, eBase );
  fRightOff[1] = textureManager.GetTexture( textureNumber + 2, eHighlight );
  fRightOff[2] = textureManager.GetTexture( textureNumber + 2, eActive );
  textureNumber = 10;
  fLeftOn[0] = textureManager.GetTexture( textureNumber, eBase );
  fLeftOn[1] = textureManager.GetTexture( textureNumber, eHighlight );
  fLeftOn[2] = textureManager.GetTexture( textureNumber, eActive );
  fBaseOn[0] = textureManager.GetTexture( textureNumber + 1, eBase );
  fBaseOn[1] = textureManager.GetTexture( textureNumber + 1, eHighlight );
  fBaseOn[2] = textureManager.GetTexture( textureNumber + 1, eActive );
  fRightOn[0] = textureManager.GetTexture( textureNumber + 2, eBase );
  fRightOn[1] = textureManager.GetTexture( textureNumber + 2, eHighlight );
  fRightOn[2] = textureManager.GetTexture( textureNumber + 2, eActive );
}

DesktopTab::~DesktopTab()
{
  fLeftOff[0] = NULL;
  fLeftOff[1] = NULL;
  fLeftOff[2] = NULL;
  fBaseOff[0] = NULL;
  fBaseOff[1] = NULL;
  fBaseOff[2] = NULL;
  fRightOff[0] = NULL;
  fRightOff[1] = NULL;
  fRightOff[2] = NULL;
  fLeftOn[0] = NULL;
  fLeftOn[1] = NULL;
  fLeftOn[2] = NULL;
  fBaseOn[0] = NULL;
  fBaseOn[1] = NULL;
  fBaseOn[2] = NULL;
  fRightOn[0] = NULL;
  fRightOn[1] = NULL;
  fRightOn[2] = NULL;
}

GUIEvent 
DesktopTab::NewEvent( const Event& event )
{
  GUIEvent retEvent;
  switch( event.type )
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
DesktopTab::Render( RWWrapper& renderApp )
{
  const sf::Rect<double> fullSize = fRect->GetRect( Rect::eResolution );
  sf::Rect<double> size = fullSize;
  size.width = 20.0;
  Sprite left( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size.left = fullSize.left + fullSize.width - 20.0;
  Sprite right( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size.left = fullSize.left + 20.0;
  size.width = fullSize.width - 40.0;
  Sprite base( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
 
  if( fOn )
    {
      if( !fPressed && !fHover )
	{
	  left.SetTexture( fLeftOn[0] );
	  base.SetTexture( fBaseOn[0] );
	  right.SetTexture( fRightOn[0] );
	}
      else if( fHover )
	{
	  left.SetTexture( fLeftOn[1] );
	  base.SetTexture( fBaseOn[1] );
	  right.SetTexture( fRightOn[1] );
	}
      else
	{
	  left.SetTexture( fLeftOn[2] );
	  base.SetTexture( fBaseOn[2] );
	  right.SetTexture( fRightOn[2] );
	}
    }
  else
    {
      if( !fPressed && !fHover )
	{
	  left.SetTexture( fLeftOff[0] );
	  base.SetTexture( fBaseOff[0] );
	  right.SetTexture( fRightOff[0] );
	}
      else if( fHover )
	{
	  left.SetTexture( fLeftOff[1] );
	  base.SetTexture( fBaseOff[1] );
	  right.SetTexture( fRightOff[1] );
	}
      else
	{
	  left.SetTexture( fLeftOff[2] );
	  base.SetTexture( fBaseOff[2] );
	  right.SetTexture( fRightOff[2] );
	}
    }
  renderApp.Draw( left );
  renderApp.Draw( base );
  renderApp.Draw( right );
}
