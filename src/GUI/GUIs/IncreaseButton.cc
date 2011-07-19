#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/IncreaseButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

IncreaseButton::IncreaseButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fButton = imageManager.NewSprite( "GUI.png" );
  fButton.SetBoundingRect( rect );
  fButton.SetSubRect( sf::Rect<int>( 400, 0, 20, 20 ) );
}

IncreaseButton::~IncreaseButton()
{
 
}

void 
IncreaseButton::RenderT( sf::RenderWindow& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 400, 0, 20, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 400, 20, 20, 20 ) );

  sf::Sprite newObject( fButton );
  newObject.SetPosition( fRect.Left, fRect.Top );
  newObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( newObject );
}

void 
IncreaseButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 400, 0, 20, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 400, 20, 20, 20 ) );

  windowApp.Draw( fButton );
}
