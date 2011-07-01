#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/TopBarButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

TopBarButton::TopBarButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fBar = imageManager.NewSprite( "FrameUI.png" );
  fBar.SetBoundingRect( rect );
  fBar.SetSubRect( sf::Rect<int>( 0, 0, 300, 20 ) );
}

TopBarButton::~TopBarButton()
{

}

void 
TopBarButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    fBar.SetSubRect( sf::Rect<int>( 0, 0, 300, 20 ) );
  else
    fBar.SetSubRect( sf::Rect<int>( 0, 20, 300, 20 ) );

  windowApp.Draw( fBar );
}
