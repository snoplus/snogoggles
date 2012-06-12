#include <Viewer/GenericTimer.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Colour.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>

namespace Viewer
{
namespace GUIs
{

GenericTimer::GenericTimer( RectPtr rect, unsigned int guiID )
  : Timer( rect, guiID )
{
  fSprite = new Sprite( rect );
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fTextures[0] = textureManager.GetTexture( 2, eBase );
  fTextures[1] = textureManager.GetTexture( 2, eHighlight );
  fTextures[2] = textureManager.GetTexture( 2, eActive );
}

GenericTimer::~GenericTimer()
{
  fTextures[0] = NULL; // Manager deletes the textures
  fTextures[1] = NULL;
  fTextures[2] = NULL;
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

