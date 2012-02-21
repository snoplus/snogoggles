using namespace std;

#include <Viewer/SpriteTimer.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/TextureManager.hh>

namespace Viewer
{
namespace GUIs
{

SpriteTimer::SpriteTimer( RectPtr rect, unsigned int guiID )
    : GenericTimer( rect, guiID )
{
  fSprite = new Sprite( rect );
}

SpriteTimer::~SpriteTimer()
{
  delete fSprite;
}

void SpriteTimer::SetTexture( const std::string& filename )
{
  TextureManager& textureManager = TextureManager::GetInstance();
  fSprite->SetTexture( textureManager.GetTexture( filename ) );
}
  
void SpriteTimer::Render( RWWrapper& windowApp )
{
  windowApp.Draw( *fSprite );
}


} // ::GUIs

} // ::Viewer

