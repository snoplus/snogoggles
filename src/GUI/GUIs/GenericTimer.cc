#include <Viewer/GenericTimer.hh>
#include <Viewer/Shape.hh>
#include <Viewer/RWWrapper.hh>
#include <SFML/Graphics.hpp>
#include <Viewer/Colour.hh>
#include <Viewer/ImageManager.hh>
#include <string>

namespace Viewer
{
namespace GUIs
{

GenericTimer::GenericTimer( const sf::Rect<double>& rect, unsigned int guiID )
    : Timer( rect, guiID )
{
    ImageManager& imageManager = ImageManager::GetInstance();

    fNormalButton = imageManager.NewSprite( "GenericButton.png" );
    fNormalButton.SetColor( sf::Color::Red );
    fNormalButton.SetBoundingRect( rect );

    fExcitedButton = fNormalButton;
    fExcitedButton.SetColor( sf::Color::Yellow );
}

void GenericTimer::Render( RWWrapper& windowApp )
{
    if( fPressed == true )
        windowApp.Draw( fExcitedButton );
    else
        windowApp.Draw( fNormalButton );

    RenderLabel( windowApp );
}


} // ::GUIs

} // ::Viewer

