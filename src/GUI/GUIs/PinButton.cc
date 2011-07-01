#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <Viewer/PinButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

PinButton::PinButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fButton = imageManager.NewSprite( "FrameUI.png" );
  fButton.SetBoundingRect( rect );
  fButton.SetSubRect( sf::Rect<int>( 301, 0, 21, 20 ) );
}

PinButton::~PinButton()
{
}

void 
PinButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    fButton.SetSubRect( sf::Rect<int>( 301, 0, 21, 20 ) );
  else
    fButton.SetSubRect( sf::Rect<int>( 301, 20, 21, 20 ) );

  windowApp.Draw( fButton );
}
