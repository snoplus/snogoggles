#include <Viewer/GenericButton.hh>
#include <Viewer/Shape.hh>
#include <Viewer/RWWrapper.hh>
#include <SFML/Graphics.hpp>
#include <Viewer/ImageManager.hh>
#include <string>

namespace Viewer
{
namespace GUIs
{

GenericButton::GenericButton( sf::Rect<double>& rect, unsigned int guiID )
    : Button( rect, guiID )
{
    ImageManager& imageManager = ImageManager::GetInstance();

    fNormalButton = imageManager.NewSprite( "GenericButton/Normal.png" );
    fNormalButton.SetBoundingRect( rect );

    fExcitedButton = imageManager.NewSprite( "GenericButton/Excited.png" );
    fExcitedButton.SetBoundingRect( rect );
}

void GenericButton::Render( RWWrapper& windowApp )
{
    if( fPressed == true )
        windowApp.Draw( fExcitedButton );
    else
        windowApp.Draw( fNormalButton );

    RenderLabel( windowApp );
}


} // ::GUIs

} // ::Viewer

