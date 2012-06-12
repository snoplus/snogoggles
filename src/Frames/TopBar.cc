#include <Viewer/TopBar.hh>
#include <Viewer/Button.hh>
#include <Viewer/Event.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

TopBar::TopBar( RectPtr rect )
  : fRect( rect )
{

}

TopBar::~TopBar()
{
  delete fLeft, fBar, fClose, fRight;
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
    case sf::Event::MouseMoved:
      {
        if( fLeft->ContainsPoint( event.GetPos() ) || fBar->ContainsPoint( event.GetPos() ) || fRight->ContainsPoint( event.GetPos() ) )
          {
            fLeft->NewEvent( event );
            fBar->NewEvent( event );
            fRight->NewEvent( event );
          }
        else
          {
            fLeft->NewEvent( Event( sf::Event::LostFocus ) );
            fBar->NewEvent( Event( sf::Event::LostFocus ) );
            fRight->NewEvent( Event( sf::Event::LostFocus ) );
          }
        if( fClose->ContainsPoint( event.GetPos() ) )
          fClose->NewEvent( event );
        else
          fClose->NewEvent( Event( sf::Event::LostFocus ) );
      }
      break;
    case sf::Event::MouseButtonReleased:
      if( fLeft->GetState() ) // Must return stop move if it is active
        break;
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
  fLeft = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 0 );
  fLeft->Initialise( 0 );
  fBar = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 1 );
  fBar->Initialise( 2 );
  fClose = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 5 );
  fClose->Initialise( 3 );
  fRight = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 6 );
  fRight->Initialise( 1 );
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
  size.Width = rect.Width - 60.0;
  size.Left = rect.Left + 20.0;
  fBar->GetRect()->SetRect( size, Rect::eResolution );
  size.Width = 20.0;
  size.Left = rect.Left + rect.Width - 40.0;
  fClose->GetRect()->SetRect( size, Rect::eResolution );
  size.Left = rect.Left + rect.Width - 20.0;
  fRight->GetRect()->SetRect( size, Rect::eResolution );
}

bool
TopBar::IsPinned()
{
  return false;
}
