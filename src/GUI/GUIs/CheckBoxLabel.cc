#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ImageManager.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

CheckBoxLabel::CheckBoxLabel( sf::Rect<double>& rect, unsigned int guiID )
  : Persist( rect, guiID )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fBox = imageManager.NewSprite( "FrameUI.png" );
  fBox.SetSubRect( sf::Rect<int>( 301, 0, 21, 20 ) );

  double buttonLength = rect.Height;
  if( rect.Height > rect.Width )
    buttonLength = rect.Width;
  else if( rect.Height == rect.Width ) // Difficult to scale
    buttonLength = rect.Width * 0.5;
  sf::Rect<double> lRect( rect.Left, rect.Top, buttonLength, buttonLength );
  sf::Rect<double> rRect( rect.Left + lRect.Width, rect.Top, rect.Width - lRect.Width, rect.Height );
  fBox.SetBoundingRect( lRect );
  

  fLabel = Text( "check box" );
  fLabel.SetBoundingRect( rRect );
  fLabel.SetColor( sf::Color( 0, 0, 0 ) );
}

CheckBoxLabel::~CheckBoxLabel()
{
}

void
CheckBoxLabel::SetLabel( const string& label )
{
  fLabel.SetString( label );
}

void 
CheckBoxLabel::RenderT( sf::RenderWindow& windowApp )
{
  // TODO if needed
}

void 
CheckBoxLabel::Render( RWWrapper& windowApp )
{
  if( !fActive )
    fBox.SetSubRect( sf::Rect<int>( 301, 0, 21, 20 ) );
  else
    fBox.SetSubRect( sf::Rect<int>( 301, 20, 21, 20 ) );

  windowApp.Draw( fLabel );
  windowApp.Draw( fBox );
}
