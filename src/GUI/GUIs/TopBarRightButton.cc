#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/TopBarRightButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

TopBarRightButton::TopBarRightButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fRight = imageManager.NewSprite( "GUI.png" );
  fRight.SetBoundingRect( sf::Rect<double>( rect.Left, rect.Top, rect.Width, rect.Height ) );
  fRight.SetSubRect( sf::Rect<int>( 460, 0, 20, 20 ) );
}

TopBarRightButton::~TopBarRightButton()
{

}


void 
TopBarRightButton::RenderT( sf::RenderWindow& windowApp )
{
  if( !fPressed )
    fRight.SetSubRect( sf::Rect<int>( 460, 0, 20, 20 ) );
  else
    fRight.SetSubRect( sf::Rect<int>( 460, 20, 20, 20 ) );
 
  sf::Sprite rightObject( fRight );
  rightObject.SetPosition( fRect.Left, fRect.Top );
  rightObject.Resize( fRect.Width, fRect.Height );
  windowApp.Draw( rightObject );
}

void 
TopBarRightButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    fRight.SetSubRect( sf::Rect<int>( 460, 0, 20, 20 ) );
  else
    fRight.SetSubRect( sf::Rect<int>( 460, 20, 20, 20 ) );

  windowApp.Draw( fRight );
}
