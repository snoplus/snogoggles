#include <Viewer/TopBar.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIImagePersist.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

TopBar::TopBar( RectPtr rect )
  : fRect( rect )
{

}

TopBar::~TopBar()
{
  delete fLeft, fBar, fDecrease, fIncrease, fPin, fClose, fRight;
}

FrameEvent
TopBar::NewEvent( const Event& event )
{
  // MUST MAKE OWN LOST FOCUS EVENTS, PHIL
  FrameEvent retEvent; // Returned event
  switch( event.Type )
    {
    case sf::Event::LostFocus:
      {
        fLeft->NewEvent( event );
        fBar->NewEvent( event );
        fDecrease->NewEvent( event );
        fIncrease->NewEvent( event );
        fPin->NewEvent( event );
        fClose->NewEvent( event );
        fRight->NewEvent( event );
        retEvent = FrameEvent( FrameEvent::eStopMove );
      }
      break;
    case sf::Event::MouseButtonPressed:
      if( fLeft->ContainsPoint( event.GetPos() ) || fBar->ContainsPoint( event.GetPos() ) || fRight->ContainsPoint( event.GetPos() ) )
        {
          fLeft->NewEvent( event );
          fBar->NewEvent( event );
          fRight->NewEvent( event );
          retEvent = FrameEvent( FrameEvent::eStartMove );
        }
      if( fPin->ContainsPoint( event.GetPos() ) )
        {
          fPin->NewEvent( event );
          retEvent = FrameEvent( FrameEvent::eStartResize );
        }
    case sf::Event::MouseMoved:
      {
        if( fLeft->ContainsPoint( event.GetPos() ) || fBar->ContainsPoint( event.GetPos() ) || fRight->ContainsPoint( event.GetPos() ) )
          {
            fLeft->NewEvent( event );
            fBar->NewEvent( event );
            fRight->NewEvent( event );
          }
        if( fClose->ContainsPoint( event.GetPos() ) )
          fClose->NewEvent( event );
      }
      break;
    case sf::Event::MouseButtonReleased:
      if( fLeft->GetState() ) // Must return stop move if it is active
        break;
      if( fPin->ContainsPoint( event.GetPos() ) )
        {
          fPin->NewEvent( event );
          retEvent = FrameEvent( FrameEvent::eStopResize );
        }
      if( fClose->ContainsPoint( event.GetPos() ) )
	{
          fClose->NewEvent( event );
          retEvent = FrameEvent( FrameEvent::eClosed );
        }
      break;
    }
  return retEvent;
}

void 
TopBar::PreInitialise( const ConfigurationTable* configTable )
{
  fLeft = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 0 );
  fLeft->Initialise( eBarLeft );
  fBar = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 1 );
  fBar->Initialise( eBar );
  fDecrease = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 2 );
  fDecrease->Initialise( eDecrease );
  fIncrease = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 3 );
  fIncrease->Initialise( eIncrease );
  fPin = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 4 );
  fPin->Initialise( ePlus );
  fClose = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 5 );
  fClose->Initialise( eCross );
  fRight = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter() ), 6 );
  fRight->Initialise( eBarRight );
}

void 
TopBar::PostInitialise( const ConfigurationTable* configTable )
{

}

void 
TopBar::SaveConfiguration( ConfigurationTable* configTable )
{

}

void 
TopBar::RenderGUI( RWWrapper& renderApp )
{
  fLeft->Render( renderApp );
  fBar->Render( renderApp );
  fDecrease->Render( renderApp );
  fIncrease->Render( renderApp );
  fPin->Render( renderApp );
  fClose->Render( renderApp );
  fRight->Render( renderApp );
}

void
TopBar::SetRect( const sf::Rect<double>& rect )
{
  sf::Rect<double> size = rect;
  fRect->SetRect( size, Rect::eResolution );
  // Left portion is 20.0 wide
  size.Width = 20.0;
  fLeft->GetRect()->SetRect( size, Rect::eResolution );
  size.Width = rect.Width - 120.0;
  size.Left = rect.Left + 20.0;
  fBar->GetRect()->SetRect( size, Rect::eResolution );
  size.Left = rect.Left + rect.Width - 100.0;
  size.Width = 20.0;
  fDecrease->GetRect()->SetRect( size, Rect::eResolution );
  size.Left = rect.Left + rect.Width - 80.0;
  fIncrease->GetRect()->SetRect( size, Rect::eResolution );
  size.Left = rect.Left + rect.Width - 60.0;
  fPin->GetRect()->SetRect( size, Rect::eResolution );
  size.Left = rect.Left + rect.Width - 40.0;
  fClose->GetRect()->SetRect( size, Rect::eResolution );
  size.Left = rect.Left + rect.Width - 20.0;
  fRight->GetRect()->SetRect( size, Rect::eResolution );
}

bool
TopBar::IsPinned()
{
  return fPin->GetState();
}
