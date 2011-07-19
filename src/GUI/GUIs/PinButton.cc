#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/PinButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

PinButton::PinButton( sf::Rect<double>& rect, unsigned int guiID )
  : Persist( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fButton = imageManager.NewSprite( "GUI.png" );
  fButton.SetBoundingRect( rect );
  fButton.SetSubRect( sf::Rect<int>( 420, 0, 20, 20 ) );
}

PinButton::~PinButton()
{

}

void 
PinButton::RenderT( sf::RenderWindow& windowApp )
{
  if( !fActive )
    fButton.SetSubRect( sf::Rect<int>( 420, 0, 20, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 420, 20, 20, 20 ) );

  sf::Sprite newObject( fButton );
  newObject.SetPosition( fRect.Left, fRect.Top );
  newObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( newObject );
}

void 
PinButton::Render( RWWrapper& windowApp )
{
  if( !fActive )
    fButton.SetSubRect( sf::Rect<int>( 420, 0, 20, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 420, 20, 20, 20 ) );

  windowApp.Draw( fButton );
}
