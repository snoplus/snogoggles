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

  fBar.SetBoundingRect( sf::Rect<double>( rect.Left + 0.1 * rect.Width, rect.Top, 0.9 * rect.Width, rect.Height ) );

  fBar.SetSubRect( sf::Rect<int>( 20, 0, 360, 20 ) );

  fTitle.SetBoundingRect( sf::Rect<double>( rect.Left + 0.1 * rect.Width, rect.Top, 0.9 * rect.Width, rect.Height ) );
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
  if( !fPressed )
    {
      fBar.SetSubRect( sf::Rect<int>( 20, 0, 360, 20 ) );
    }
  else
    {
      fBar.SetSubRect( sf::Rect<int>( 20, 20, 360, 20 ) );
    }

  windowApp.Draw( fBar );
  windowApp.Draw( fTitle );
}
