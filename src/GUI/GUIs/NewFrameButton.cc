#include <SFML/Graphics/Rect.hpp>

using namespace std;

#include <Viewer/NewFrameButton.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/Sprite.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

NewFrameButton::~NewFrameButton()
{
  delete fText;
}

void 
NewFrameButton::Initialise( const string& frameName )
{
  GUITextureManager& textureManager = GUITextureManager::GetInstance();
  fLeft[0] = textureManager.GetTexture( eBarLeft, eBase );
  fLeft[1] = textureManager.GetTexture( eBarLeft, eHighlight );
  fLeft[2] = textureManager.GetTexture( eBarLeft, eActive );
  fBar[0] = textureManager.GetTexture( eBar, eBase );
  fBar[1] = textureManager.GetTexture( eBar, eHighlight );
  fBar[2] = textureManager.GetTexture( eBar, eActive );
  fRight[0] = textureManager.GetTexture( eBarRight, eBase );
  fRight[1] = textureManager.GetTexture( eBarRight, eHighlight );
  fRight[2] = textureManager.GetTexture( eBarRight, eActive );

  // This button should never move (only one purpose) thus this is safe
  sf::Rect<double> masterSize = fRect->GetRect( Rect::eResolution );
  sf::Rect<double> size = masterSize;
  size.Left += 20.0;
  size.Width -= 40.0;
  fText = new Text( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  fText->SetString( frameName );
  fFrameName = frameName;

  fBarSprite = new Sprite( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size.Left = masterSize.Left; size.Width = 20.0;
  fLeftSprite = new Sprite( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
  size.Left = masterSize.Left + masterSize.Width - 20.0;
  fRightSprite = new Sprite( RectPtr( fRect->NewDaughter( size, Rect::eResolution ) ) );
}

void 
NewFrameButton::Render( RWWrapper& renderApp )
{
  if( !fPressed && !fHover )
    {
      fLeftSprite->SetTexture( fLeft[0] );
      fBarSprite->SetTexture( fBar[0] );
      fRightSprite->SetTexture( fRight[0] );
    }
  else if( fHover )
    {
      fLeftSprite->SetTexture( fLeft[1] );
      fBarSprite->SetTexture( fBar[1] );
      fRightSprite->SetTexture( fRight[1] );
    }
  else
    {
      fLeftSprite->SetTexture( fLeft[2] );
      fBarSprite->SetTexture( fBar[2] );
      fRightSprite->SetTexture( fRight[2] );
    }
  renderApp.Draw( *fLeftSprite );
  renderApp.Draw( *fBarSprite );
  renderApp.Draw( *fRightSprite );
  renderApp.Draw( *fText );
}

