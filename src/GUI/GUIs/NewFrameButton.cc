#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include <Viewer/NewFrameButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

NewFrameButton::NewFrameButton( sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fBar = imageManager.NewSprite( "GUI.png" );

  fBar.SetBoundingRect( sf::Rect<double>( rect.Left, rect.Top, rect.Width, rect.Height ) );

  fBar.SetSubRect( sf::Rect<int>( 0, 40, 120, 40 ) );

  fTitle.SetBoundingRect( sf::Rect<double>( rect.Left + 0.1 * rect.Width, rect.Top + 0.3 * rect.Height, 0.8 * rect.Width, 0.6 * rect.Height ) );
}

NewFrameButton::~NewFrameButton()
{

}

void
NewFrameButton::SetTitle( const string& title )
{
  fTitle.SetString( title );
}

void 
NewFrameButton::Render( RWWrapper& windowApp )
{
  if( !fHover )
    {
      fBar.SetSubRect( sf::Rect<int>( 0, 40, 120, 40 ) );
    }
  else
    {
      fBar.SetSubRect( sf::Rect<int>( 120, 40, 120, 40 ) );
    }
  if( !fPressed )
    fTitle.SetColor( sf::Color( 255, 255, 255 ) );
  else
    fTitle.SetColor( sf::Color( 255, 216, 64 ) );

  windowApp.Draw( fBar );
  windowApp.Draw( fTitle );
}
