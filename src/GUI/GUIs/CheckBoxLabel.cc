#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIImageManager.hh>
#include <Viewer/GUIColourPalette.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

CheckBoxLabel::CheckBoxLabel( const sf::Rect<double>& rect, unsigned int guiID )
  : Persist( rect, guiID )
{
  GUIImageManager& imageManager = GUIImageManager::GetInstance();
  fBox[0] = imageManager.NewSprite( eOpenBox, eBase );
  fBox[1] = imageManager.NewSprite( eCrossBox, eHighlight );

  double buttonLength = rect.Height;
  if( rect.Height > rect.Width )
    buttonLength = rect.Width;
  else if( rect.Height == rect.Width ) // Difficult to scale
    buttonLength = rect.Width * 0.5;
  sf::Rect<double> lRect( rect.Left, rect.Top, buttonLength, buttonLength );
  sf::Rect<double> rRect( rect.Left + lRect.Width, rect.Top, rect.Width - lRect.Width, rect.Height );
  fBox[0].SetBoundingRect( lRect );
  fBox[1].SetBoundingRect( lRect );  

  fLabel = Text( "check box" );
  fLabel.SetBoundingRect( rRect );
  fLabel.SetColor( GUIColourPalette::gPalette->GetTextColour( eBase ) );
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
  if( !fPressed )
    windowApp.Draw( fBox[0] );
  else
    windowApp.Draw( fBox[1] );

  windowApp.Draw( fLabel );

}
