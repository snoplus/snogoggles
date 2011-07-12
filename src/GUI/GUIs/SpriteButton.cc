#include <Viewer/SpriteButton.hh>
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

SpriteButton::SpriteButton( sf::Rect<double>& rect, unsigned int guiID )
    : GenericButton( rect, guiID )
{

}

SpriteButton::~SpriteButton()
{

}

void SpriteButton::SetSprite( const std::string& filename )
{
    ImageManager& imageManager = ImageManager::GetInstance();
    fSprite = imageManager.NewSprite( filename );
    fSprite.SetBoundingRect( fRect );
}

void SpriteButton::RenderLabel( RWWrapper& windowApp )
{
    windowApp.Draw( fSprite );
}


} // ::GUIs

} // ::Viewer

