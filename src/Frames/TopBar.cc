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
  delete fLeftButton, fBarButton, fCloseButton, fRightButton;
}

FrameEvent
TopBar::NewEvent( const Event& event )
{
  // MUST MAKE OWN LOST FOCUS EVENTS, PHIL
  FrameEvent retEvent; // Returned event
  switch( event.type )
    {
    case sf::Event::LostFocus:
      {
        fLeftButton->NewEvent( event );
        fBarButton->NewEvent( event );
        fCloseButton->NewEvent( event );
        fRightButton->NewEvent( event );
        retEvent = FrameEvent( FrameEvent::eStopMove );
      }
      break;
    case sf::Event::MouseButtonPressed:
      if( fLeftButton->ContainsPoint( event.GetPos() ) || fBarButton->ContainsPoint( event.GetPos() ) || fRightButton->ContainsPoint( event.GetPos() ) )
        {
          fLeftButton->NewEvent( event );
          fBarButton->NewEvent( event );
          fRightButton->NewEvent( event );
          retEvent = FrameEvent( FrameEvent::eStartMove );
        }
    case sf::Event::MouseMoved:
      {
        if( fLeftButton->ContainsPoint( event.GetPos() ) || fBarButton->ContainsPoint( event.GetPos() ) || fRightButton->ContainsPoint( event.GetPos() ) )
          {
            fLeftButton->NewEvent( event );
            fBarButton->NewEvent( event );
            fRightButton->NewEvent( event );
          }
        else
          {
            fLeftButton->NewEvent( Event( sf::Event::LostFocus ) );
            fBarButton->NewEvent( Event( sf::Event::LostFocus ) );
            fRightButton->NewEvent( Event( sf::Event::LostFocus ) );
          }
        if( fCloseButton->ContainsPoint( event.GetPos() ) )
          fCloseButton->NewEvent( event );
        else
          fCloseButton->NewEvent( Event( sf::Event::LostFocus ) );
      }
      break;
    case sf::Event::MouseButtonReleased:
      if( fLeftButton->GetState() ) // Must return stop move if it is active
        break;
      if( fCloseButton->ContainsPoint( event.GetPos() ) )
        {
          fCloseButton->NewEvent( event );
          retEvent = FrameEvent( FrameEvent::eClosed );
        }
      break;
    }
  return retEvent;
}

void 
TopBar::PreInitialise( const ConfigurationTable* configTable )
{
  fLeftButton = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 0 );
  fLeftButton->Initialise( 0 );
  fBarButton = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 1 );
  fBarButton->Initialise( 1 );
  fCloseButton = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 5 );
  fCloseButton->Initialise( 6 );
  fRightButton = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 6 );
  fRightButton->Initialise( 2 );
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
  fLeftButton->Render( renderApp );
  fBarButton->Render( renderApp );
  fCloseButton->Render( renderApp );
  fRightButton->Render( renderApp );
}

void
TopBar::SetRect( const sf::Rect<double>& rect )
{
  sf::Rect<double> size = rect;
  fRect->SetRect( size, Rect::eResolution );
  size.height = 20.0;
  // Left portion is 20.0 wide
  size.width = 20.0;
  fLeftButton->GetRect()->SetRect( size, Rect::eResolution );
  size.width = rect.width - 60.0;
  size.left = rect.left + 20.0;
  fBarButton->GetRect()->SetRect( size, Rect::eResolution );
  size.width = 20.0;
  size.left = rect.left + rect.width - 40.0;
  fCloseButton->GetRect()->SetRect( size, Rect::eResolution );
  size.left = rect.left + rect.width - 20.0;
  fRightButton->GetRect()->SetRect( size, Rect::eResolution );
}

bool
TopBar::IsPinned()
{
  return false;
}
