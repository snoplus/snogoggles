#include <Viewer/GUIImageButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Sprite.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIImageButton::GUIImageButton( RectPtr rect, 
				unsigned int guiID )
  : Button( rect, guiID )
{

}

void
GUIImageButton::Initialise( EGUITexture image )
{
  GUITextureManager& textureManager = GUITextureManager::GetInstance();
  fButton[0] = textureManager.GetTexture( image, eBase );
  fButton[1] = textureManager.GetTexture( image, eHighlight );
  fButton[2] = textureManager.GetTexture( image, eActive );
}

GUIImageButton::~GUIImageButton()
{
 
}

void 
GUIImageButton::Render( RWWrapper& renderApp )
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
