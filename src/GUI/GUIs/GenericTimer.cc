#include <Viewer/GenericTimer.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Colour.hh>
#include <Viewer/GUITextureManager.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{
namespace GUIs
{

GenericTimer::GenericTimer( RectPtr rect, unsigned int guiID )
  : Timer( rect, guiID )
{
  fSprite = new Sprite( rect );
  GUITextureManager& textureManager = GUITextureManager::GetInstance();
  fTextures[0] = textureManager.GetTexture( eNewFrame, eBase );
  fTextures[1] = textureManager.GetTexture( eNewFrame, eHighlight );
  fTextures[2] = textureManager.GetTexture( eNewFrame, eActive );
}

GenericTimer::~GenericTimer()
{
  delete fSprite;
}

void GenericTimer::Render( RWWrapper& windowApp )
{
  if( fPressed == true )
    fSprite->SetTexture( fTextures[2] );
  //  else if( fHover )
  //  fSprite->SetTexture( fTextures[1] );
  else
    fSprite->SetTexture( fTextures[0] );
  
  windowApp.Draw( *fSprite );
}


} // ::GUIs

} // ::Viewer

