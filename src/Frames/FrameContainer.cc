#include <SFML/Window/Event.hpp>

#include <string>
using namespace std;

#include <Viewer/FrameContainer.hh>
#include <Viewer/Frame.hh>
#include <Viewer/Logo.hh>
#include <Viewer/ExitButton.hh>
#include <Viewer/PinButton.hh>
#include <Viewer/TopBarButton.hh>
#include <Viewer/UIEvent.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

FrameContainer::FrameContainer( ConfigurationTable& configTable )
{      
  string frameType = configTable.GetS( "type" );
  fFrame = fFrameFactory.New( frameType );

  sf::Rect<double> exitPos( 0.95, 0.0, 0.05, 0.9 );
  fExitButton = new GUIs::ExitButton( exitPos, 0 );
  sf::Rect<double> pinPos( 0.9, 0.0, 0.05, 0.9 );
  fPinButton = new GUIs::PinButton( pinPos, 1 );
  sf::Rect<double> barPos( 0.0, 0.0, 0.9, 0.9 );
  fTopBar = new GUIs::TopBarButton( barPos, 3 );  

  sf::Vector2<double> pos( configTable.GetI( "posX" ), configTable.GetI( "posY" ) );
  sf::Vector2<double> size( configTable.GetI( "sizeX" ), configTable.GetI( "sizeY" ) );
  Move( pos );
  Resize( size );

  fFrame->Initialise( configTable );
} 

FrameContainer::~FrameContainer()
{
  delete fExitButton;
  delete fFrame;
}
  
void
FrameContainer::EventLoop()
{
  fFrame->EventLoop();
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
  RWWrapper rWindowApp( windowApp, fTopBarCoord );
  fExitButton->Render( rWindowApp );
  fPinButton->Render( rWindowApp );
  fTopBar->Render( rWindowApp );
  fFrame->RenderGUI( windowApp );
}

FrameUIReturn 
FrameContainer::NewEvent( sf::Event& event )
{
  FrameUIReturn returnEvent;
  UIEvent uiEvent = UIEvent( event, fTopBarCoord );
  switch( event.Type )
    {
// Some events may be relevant to the top bar
    case sf::Event::MouseButtonPressed:
      {
	if( fTopBar->ContainsPoint( uiEvent.GetLocalCoord() ) )
	  {
	    fTopBar->NewEvent( uiEvent );
	    returnEvent = FrameUIReturn( FrameUIReturn::eStartMove );
	  }
	if( fExitButton->ContainsPoint( uiEvent.GetLocalCoord() ) )
	  fExitButton->NewEvent( uiEvent );
	if( fPinButton->ContainsPoint( uiEvent.GetLocalCoord() ) )
	  fPinButton->NewEvent( uiEvent );
      }
      break;
    case sf::Event::MouseButtonReleased:
      {
	if( fExitButton->GetState() )
	  fExitButton->NewEvent( uiEvent );
	if( fExitButton->ContainsPoint( uiEvent.GetLocalCoord() ) )
	  returnEvent = FrameUIReturn( FrameUIReturn::eClosed );

	if( fPinButton->GetState() )
	  returnEvent = FrameUIReturn( FrameUIReturn::ePinned );
	if( fPinButton->ContainsPoint( uiEvent.GetLocalCoord() ) )
	  fPinButton->NewEvent( uiEvent );

	if( fTopBar->GetState() ) // Always Stop moving if mouse up
	  {
	    fTopBar->NewEvent( uiEvent );
	    returnEvent = FrameUIReturn( FrameUIReturn::eStopMove );
	  }
      }
      break;
    }
 fFrame->NewEvent( event );
 return returnEvent;
}
  
void 
FrameContainer::SaveConfiguration( ConfigurationTable& configTable )
{
  configTable.SetS( "type", fFrame->GetName() );
  FrameCoord full = GetContainerCoord();
  sf::Rect<double> rect = full.GetRect();
  configTable.SetI( "posX", static_cast<int>( rect.Left ) );
  configTable.SetI( "posY", static_cast<int>( rect.Top ) );
  configTable.SetI( "sizeX", static_cast<int>( rect.Width ) );
  configTable.SetI( "sizeY", static_cast<int>( rect.Height ) );
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
  const double barHeight = 20.0; // Height of the Top bar
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
