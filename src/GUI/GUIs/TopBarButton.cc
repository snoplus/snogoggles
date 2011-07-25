#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include <Viewer/TopBarButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

TopBarButton::TopBarButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fBar = imageManager.NewSprite( "GUI.png" );
  fLeft = imageManager.NewSprite( "GUI.png" );

  fBar.SetBoundingRect( sf::Rect<double>( rect.Left + 0.1 * rect.Width, rect.Top, 0.9 * rect.Width, rect.Height ) );
  fLeft.SetBoundingRect( sf::Rect<double>( rect.Left, rect.Top, 0.1 * rect.Width, rect.Height ) );

  fBar.SetSubRect( sf::Rect<int>( 20, 0, 360, 20 ) );
  fLeft.SetSubRect( sf::Rect<int>( 0, 0, 20, 20 ) );

  fTitle.SetBoundingRect( sf::Rect<double>( rect.Left + 0.1 * rect.Width, rect.Top, 0.9 * rect.Width, rect.Height ) );
}

TopBarButton::~TopBarButton()
{

}

void
TopBarButton::SetTitle( const string& title )
{
  fTitle.SetString( title );
}

void 
TopBarButton::RenderT( sf::RenderWindow& windowApp )
{
  if( !fPressed )
    {
      fBar.SetSubRect( sf::Rect<int>( 20, 0, 360, 20 ) );
      fLeft.SetSubRect( sf::Rect<int>( 0, 0, 20, 20 ) );
    }
  else
    {
      fBar.SetSubRect( sf::Rect<int>( 20, 20, 360, 20 ) );
      fLeft.SetSubRect( sf::Rect<int>( 0, 20, 20, 20 ) );
    }

  sf::Sprite barObject( fBar );
  barObject.SetPosition( fRect.Left + 20, fRect.Top );
  barObject.Resize( fRect.Width - 20, fRect.Height );
  windowApp.Draw( barObject );  

  sf::Sprite leftObject( fLeft );
  leftObject.SetPosition( fRect.Left, fRect.Top );
  leftObject.Resize( 20, fRect.Height );
  windowApp.Draw( leftObject );

  sf::Text titleObject( fTitle );
  sf::Rect<float> textRect = titleObject.GetRect();
  titleObject.SetPosition( fRect.Left + 20, fRect.Top - 1 );
  titleObject.Scale( fRect.Height / textRect.Height, fRect.Height / textRect.Height );
  windowApp.Draw( titleObject );
}

void 
TopBarButton::Render( RWWrapper& windowApp )
{
  if( !fPressed )
    {
      fBar.SetSubRect( sf::Rect<int>( 20, 0, 360, 20 ) );
      fLeft.SetSubRect( sf::Rect<int>( 0, 0, 20, 20 ) );
    }
  else
    {
      fBar.SetSubRect( sf::Rect<int>( 20, 20, 360, 20 ) );
      fLeft.SetSubRect( sf::Rect<int>( 0, 20, 20, 20 ) );
    }

  windowApp.Draw( fBar );
  windowApp.Draw( fLeft );
  windowApp.Draw( fTitle, RWWrapper::eHeight );
}
