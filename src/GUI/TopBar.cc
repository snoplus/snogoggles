#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include <Viewer/TopBar.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

TopBar::TopBar()
  : fLeft( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 0 ),
    fBar( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 1 ),
    fDecrease( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 2 ),
    fIncrease( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 3 ),
    fPin( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 4 ),
    fClose( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 5 ),
    fRight( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ), 6 )
{
  fLeft.Initialise( eBarLeft );
  fBar.Initialise( eBar );
  fDecrease.Initialise( eDecrease );
  fIncrease.Initialise( eIncrease );
  fPin.Initialise( ePlus );
  fClose.Initialise( eCross );
  fRight.Initialise( eBarRight );
}

TopBar::~TopBar()
{

}

void 
TopBar::SetRect( const sf::Rect<double>& rect )
{
  fRect = rect;
  fLeft.SetRect( sf::Rect<double>( rect.Left, rect.Top, 20.0, 20.0 ) );
  fBar.SetRect( sf::Rect<double>( rect.Left + 20.0, rect.Top, rect.Width - 120.0, 20.0 ) );
  fDecrease.SetRect( sf::Rect<double>( rect.Left + rect.Width - 100.0, rect.Top, 20.0, 20.0 ) );
  fIncrease.SetRect( sf::Rect<double>( rect.Left + rect.Width - 80.0, rect.Top, 20.0, 20.0 ) );
  fPin.SetRect( sf::Rect<double>( rect.Left + rect.Width - 60.0, rect.Top, 20.0, 20.0 ) );
  fClose.SetRect( sf::Rect<double>( rect.Left + rect.Width - 40.0, rect.Top, 20.0, 20.0 ) );
  fRight.SetRect( sf::Rect<double>( rect.Left + rect.Width - 20.0, rect.Top, 20.0, 20.0 ) );
}

void
TopBar::SetTitle( const string& title )
{
  fTitle.SetString( title );
}

void 
TopBar::RenderT( sf::RenderWindow& windowApp )
{
  fLeft.RenderT( windowApp );
  fBar.RenderT( windowApp );
  fDecrease.RenderT( windowApp );
  fIncrease.RenderT( windowApp );
  fPin.RenderT( windowApp );
  fClose.RenderT( windowApp );
  fRight.RenderT( windowApp );

  sf::Text titleObject( fTitle );
  sf::Rect<float> textRect = titleObject.GetRect();
  titleObject.SetPosition( fRect.Left + 20.0, fRect.Top - 1 );
  titleObject.Scale( fRect.Height / textRect.Height, fRect.Height / textRect.Height );
  windowApp.Draw( titleObject );
}

FrameUIReturn
TopBar::NewEvent( UIEvent& event )
{
  FrameUIReturn retEvent; // Returned event
  switch( event.Type )
    {
    case sf::Event::LostFocus:
      fLeft.NewEvent( event );
      fBar.NewEvent( event );
      fDecrease.NewEvent( event );
      fIncrease.NewEvent( event );
      fPin.NewEvent( event );
      fClose.NewEvent( event );
      fRight.NewEvent( event );
      retEvent = FrameUIReturn( FrameUIReturn::eStopMove );
      break;
    case sf::Event::MouseButtonPressed:
      if( fLeft.ContainsPoint( event.GetResolutionCoord() ) || 
	  fBar.ContainsPoint( event.GetResolutionCoord() ) ||
	  fRight.ContainsPoint( event.GetResolutionCoord() ) )
	{
	  fLeft.NewEvent( event );
	  fBar.NewEvent( event );
	  fRight.NewEvent( event );
	  retEvent = FrameUIReturn( FrameUIReturn::eStartMove );
	}
    case sf::Event::MouseMoved:
      if( fLeft.ContainsPoint( event.GetResolutionCoord() ) || 
	  fBar.ContainsPoint( event.GetResolutionCoord() ) ||
	  fRight.ContainsPoint( event.GetResolutionCoord() ) )
	{
	  fLeft.NewEvent( event );
	  fBar.NewEvent( event );
	  fRight.NewEvent( event );
	}
      if( fDecrease.ContainsPoint( event.GetResolutionCoord() ) )
	fDecrease.NewEvent( event );
      if( fIncrease.ContainsPoint( event.GetResolutionCoord() ) )
	fIncrease.NewEvent( event );
      if( fPin.ContainsPoint( event.GetResolutionCoord() ) )
	fPin.NewEvent( event );
      if( fClose.ContainsPoint( event.GetResolutionCoord() ) )
	fClose.NewEvent( event );
      break;
    case sf::Event::MouseButtonReleased:
      retEvent = FrameUIReturn( FrameUIReturn::eStopMove ); // Default only overide if something else happens
      if( fLeft.GetState() ) // Must return stop move if it is active
	break;

      if( fDecrease.ContainsPoint( event.GetResolutionCoord() ) )
	{
	  fDecrease.NewEvent( event );
	  retEvent = FrameUIReturn( FrameUIReturn::eDecrease );
	}
      if( fIncrease.ContainsPoint( event.GetResolutionCoord() ) )
	{
	  fIncrease.NewEvent( event );
	  retEvent = FrameUIReturn( FrameUIReturn::eIncrease );
	}
      if( fPin.ContainsPoint( event.GetResolutionCoord() ) )
	{
	  fPin.NewEvent( event );
	  retEvent = FrameUIReturn( FrameUIReturn::ePinned );
	}
      if( fClose.ContainsPoint( event.GetResolutionCoord() ) )
	{
	  fClose.NewEvent( event );
	  retEvent = FrameUIReturn( FrameUIReturn::eClosed );
	}
      break;
    }
  return retEvent;
}

bool 
TopBar::ContainsPoint( const sf::Vector2<double>& resolutionCoord )
{
  const double localX = resolutionCoord.x - fRect.Left;
  const double localY = resolutionCoord.y - fRect.Top;
  if( localX > 0 && localX < fRect.Width && localY > 0 && localY < fRect.Height )
    return true;
  else
    return false;
}


