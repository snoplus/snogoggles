#include <Viewer/GUIImagePersist.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Sprite.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

GUIImagePersist::GUIImagePersist( RectPtr rect, unsigned int guiID )
  : Persist( rect, guiID )
{

}

void
GUIImagePersist::Initialise( EGUITexture image )
{
  GUITextureManager& textureManager = GUITextureManager::GetInstance();
  fPersist[0] = textureManager.GetTexture( image, eBase );
  fPersist[1] = textureManager.GetTexture( image, eHighlight );
  fPersist[2] = textureManager.GetTexture( image, eActive );
}

GUIImagePersist::~GUIImagePersist()
{
  fPersist[0] = NULL; // Manager deletes the texture
  fPersist[1] = NULL;
  fPersist[2] = NULL;
}

void 
GUIImagePersist::Render( RWWrapper& renderApp )
{
  Sprite buttonSprite( fRect );
  
  if( !fPressed && !fHover )
    buttonSprite.SetTexture( fPersist[0] );
  else if( fHover )
    buttonSprite.SetTexture( fPersist[1] );
  else
    buttonSprite.SetTexture( fPersist[2] );
  renderApp.Draw( buttonSprite );
}
