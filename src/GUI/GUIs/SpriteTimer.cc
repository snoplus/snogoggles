#include <Viewer/SpriteTimer.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/RWWrapper.hh>
#include <SFML/Graphics.hpp>
#include <Viewer/ImageManager.hh>
#include <string>

#include <iostream>

namespace Viewer
{
namespace GUIs
{

SpriteTimer::SpriteTimer( const sf::Rect<double>& rect, unsigned int guiID )
    : GenericTimer( rect, guiID )
{

}

SpriteTimer::~SpriteTimer()
{

}

void SpriteTimer::SetSprite( const std::string& filename )
{
    ImageManager& imageManager = ImageManager::GetInstance();
    fSprite = imageManager.NewSprite( filename );
    fSprite.SetBoundingRect( fRect );
}

void SpriteTimer::RenderLabel( RWWrapper& windowApp )
{
    windowApp.Draw( fSprite );
}


} // ::GUIs

} // ::Viewer

