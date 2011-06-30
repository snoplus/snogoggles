#include <SFML/Window/Event.hpp>

#include <Viewer/FrameContainer.hh>
#include <Viewer/Frame.hh>
#include <Viewer/Logo.hh>
#include <Viewer/ExitButton.hh>
#include <Viewer/PinButton.hh>
using namespace Viewer;

void 
FrameContainer::Initialise( ConfigurationTable& configTable )
{
  sf::Rect<double> exitPos( 0.95, 0.0, 0.05, 0.9 );
  fExitButton = new GUIs::ExitButton( exitPos, 0 );
  sf::Rect<double> pinPos( 0.85, 0.0, 0.05, 0.9 );
  fPinButton = new GUIs::PinButton( pinPos, 1 );
  sf::Rect<double> barPos( 0.0, 0.0, 0.6, 0.9 );
  fTopBar = new GUIs::PinButton( barPos, 3 );
  // Temp below
  fFrame = new Frames::Logo();
  fFrame->Initialise( configTable );
}

FrameContainer::~FrameContainer()
{
  delete fExitButton;
  delete fFrame;
}
  
void 
FrameContainer::Render2d( sf::RenderWindow& windowApp )
{
  fFrame->Render2dT( windowApp );
}

void 
FrameContainer::Render3d( sf::RenderWindow& windowApp )
{
  fFrame->Render3dT( windowApp );
}

void 
FrameContainer::RenderGUI( sf::RenderWindow& windowApp )
{
  fExitButton->Render( windowApp, fTopBarCoord );
  fPinButton->Render( windowApp, fTopBarCoord );
  fTopBar->Render( windowApp, fTopBarCoord );
  fFrame->RenderGUI( windowApp );
}

FrameEvent 
FrameContainer::NewEvent( sf::Event& event )
{
  switch( event.Type )
    {
// Some events may be relevant to the top bar
    case sf::Event::MouseButtonPressed:
      {
	sf::Vector2<double> localPosition = fTopBarCoord.ResolutionToFrameCoord( FrameCoord::WindowToResolutionCoord( sf::Vector2<double>( event.MouseButton.X, event.MouseButton.Y ) ) );
	
	if( fTopBar->ContainsPoint( localPosition ) )
	  {
	    fTopBar->NewEvent( event );
	    return FrameEvent( FrameEvent::eStartMove );
	  }
	if( fExitButton->ContainsPoint( localPosition ) )
	  fExitButton->NewEvent( event );
	if( fPinButton->ContainsPoint( localPosition ) )
	  fPinButton->NewEvent( event );
      }
      break;
    case sf::Event::MouseButtonReleased:
      {
	sf::Vector2<double> localPosition = fTopBarCoord.ResolutionToFrameCoord( FrameCoord::WindowToResolutionCoord( sf::Vector2<double>( event.MouseButton.X, event.MouseButton.Y ) ) );
	
	if( fExitButton->ContainsPoint( localPosition ) )
	  fExitButton->NewEvent( event );
	if( fPinButton->ContainsPoint( localPosition ) )
	  fPinButton->NewEvent( event );
	if( fTopBar->GetState() ) // Always ??
	  {
	    fTopBar->NewEvent( event );
	    return FrameEvent( FrameEvent::eStopMove );
	  }
      }
      break;
    }
 fFrame->NewEvent( event );
 return FrameEvent();
}
  
void 
FrameContainer::SaveConfiguration( ConfigurationTable& configTable )
{
  fFrame->SaveConfiguration( configTable );
}

void 
FrameContainer::Resize( const sf::Vector2<double>& size )
{
  FrameCoord full = GetContainerCoord();
  sf::Rect<double> rect = full.GetRect();
  rect.Width = size.x;
  rect.Height = size.y;
  full.SetRect( rect );
  SetContainerCoord( full );
}

void 
FrameContainer::Move( const sf::Vector2<double>& position )
{
  FrameCoord full = GetContainerCoord();
  sf::Rect<double> rect = full.GetRect();
  rect.Left = position.x;
  rect.Top = position.y;
  full.SetRect( rect );
  SetContainerCoord( full );
}


void 
FrameContainer::SetContainerCoord( FrameCoord& fContainerCoord )
{
  const double barHeight = 10.0; // Height of the Top bar
  sf::Rect<double> rect = fContainerCoord.GetRect();
  sf::Rect<double> frameRect( rect.Left, rect.Top + barHeight,
			      rect.Width, rect.Height - barHeight );
  sf::Rect<double> barRect( rect.Left, rect.Top,
			    rect.Width, barHeight );
  fTopBarCoord = FrameCoord( barRect );  
  fFrame->SetFrameCoord( FrameCoord( frameRect ) );
}

FrameCoord
FrameContainer::GetContainerCoord()
{
  sf::Rect<double> rect( fTopBarCoord.GetRect().Left, // Must be left
			 fTopBarCoord.GetRect().Top, // Must be top
			 fTopBarCoord.GetRect().Width, // Must be consistent
			 fTopBarCoord.GetRect().Height + fFrame->GetFrameCoord().GetRect().Height );
  return FrameCoord( rect );
}
