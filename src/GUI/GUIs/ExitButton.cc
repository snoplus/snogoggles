#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/ExitButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

ExitButton::ExitButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fButton = imageManager.NewSprite( "FrameUI.png" );
  fButton.SetBoundingRect( rect );
  fButton.SetSubRect( sf::Rect<int>( 323, 0, 21, 20 ) );
}

ExitButton::~ExitButton()
{
 
}

void 
ExitButton::RenderT( sf::RenderWindow& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 323, 0, 21, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 323, 20, 21, 20 ) );

  sf::Sprite newObject( fButton );
  newObject.SetPosition( fRect.Left, fRect.Top );
  newObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( newObject );
}

void 
ExitButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 323, 0, 21, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 323, 20, 21, 20 ) );

  windowApp.Draw( fButton );
}
