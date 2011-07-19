#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/DecreaseButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

DecreaseButton::DecreaseButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fButton = imageManager.NewSprite( "GUI.png" );
  fButton.SetBoundingRect( rect );
  fButton.SetSubRect( sf::Rect<int>( 380, 0, 20, 20 ) );
}

DecreaseButton::~DecreaseButton()
{
 
}

void 
DecreaseButton::RenderT( sf::RenderWindow& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 380, 0, 20, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 380, 20, 20, 20 ) );

  sf::Sprite newObject( fButton );
  newObject.SetPosition( fRect.Left, fRect.Top );
  newObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( newObject );
}

void 
DecreaseButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 380, 0, 20, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 380, 20, 20, 20 ) );

  windowApp.Draw( fButton );
}
