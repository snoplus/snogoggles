#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include <Viewer/NewFrameButton.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIImageManager.hh>
#include <Viewer/GUIColourPalette.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

NewFrameButton::NewFrameButton( const sf::Rect<double>& rect, unsigned int guiID )
  : Button( rect, guiID )
{
  GUIImageManager& imageManager = GUIImageManager::GetInstance();
  fLeft[0] = imageManager.NewSprite( eNewFrameLeft, eBase );
  fLeft[1] = imageManager.NewSprite( eNewFrameLeft, eHighlight );
  fLeft[2] = imageManager.NewSprite( eNewFrameLeft, eActive );

  fBar[0] = imageManager.NewSprite( eNewFrame, eBase );
  fBar[1] = imageManager.NewSprite( eNewFrame, eHighlight );
  fBar[2] = imageManager.NewSprite( eNewFrame, eActive );

  fRight[0] = imageManager.NewSprite( eNewFrameRight, eBase );
  fRight[1] = imageManager.NewSprite( eNewFrameRight, eHighlight );
  fRight[2] = imageManager.NewSprite( eNewFrameRight, eActive );

  SetRect( rect );
}

NewFrameButton::~NewFrameButton()
{

}

void
NewFrameButton::SetPositions( const sf::Rect<double>& rect )
{
  sf::Rect<double> leftRect( rect.Left, rect.Top, rect.Width * 0.2, rect.Height );
  fLeft[0].SetBoundingRect( leftRect );
  fLeft[1].SetBoundingRect( leftRect );
  fLeft[2].SetBoundingRect( leftRect );

  sf::Rect<double> barRect( rect.Left + rect.Width * 0.2, rect.Top, rect.Width * 0.6, rect.Height );
  fBar[0].SetBoundingRect( barRect );
  fBar[1].SetBoundingRect( barRect );
  fBar[2].SetBoundingRect( barRect );

  sf::Rect<double> rightRect( rect.Left + rect.Width * 0.8, rect.Top, rect.Width * 0.2, rect.Height );
  fRight[0].SetBoundingRect( rightRect );
  fRight[1].SetBoundingRect( rightRect );
  fRight[2].SetBoundingRect( rightRect );

  fTitle.SetBoundingRect( barRect );
}

void
NewFrameButton::SetTitle( const string& title )
{
  fTitle.SetString( title );
}

void 
NewFrameButton::Render( RWWrapper& windowApp )
{
  SetPositions( fRect );
  if( !fPressed && !fHover )
    {
      windowApp.Draw( fLeft[0] );
      windowApp.Draw( fBar[0] );
      windowApp.Draw( fRight[0] );
    }
  else if( fHover )
    {
      windowApp.Draw( fLeft[1] );
      windowApp.Draw( fBar[1] );
      windowApp.Draw( fRight[1] );
    }
  else
    {
      windowApp.Draw( fLeft[2] );
      windowApp.Draw( fBar[2] );
      windowApp.Draw( fRight[2] );
    }

  if( !fPressed )
    fTitle.SetColor( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  else
    fTitle.SetColor( GUIColourPalette::gPalette->GetTextColour( eActive ) );

  windowApp.Draw( fTitle );
}
