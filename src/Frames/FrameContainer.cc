#include <SFML/Window/Event.hpp>

#include <string>
#include <iostream>
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

FrameContainer::FrameContainer()
{

}

void 
FrameContainer::Initialise( const string& type )
{
  fFrame = fFrameFactory.New( type );  
  sf::Rect<double> tempPos( 0.0, 0.0, 1.0, 1.0 );
  fExitButton = new GUIs::ExitButton( tempPos, 0 );
  fPinButton = new GUIs::PinButton( tempPos, 1 );
  fTopBar = new GUIs::TopBarButton( tempPos, 3 );  

  fFrame->Initialise();
}

void 
FrameContainer::Initialise( ConfigurationTable& configTable )
{      
  string frameType = configTable.GetS( "type" );
  Initialise( frameType );

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
FrameContainer::Render3d()
{
  fFrame->Render3d();
}

void 
FrameContainer::RenderGUI( sf::RenderWindow& windowApp )
{
  sf::Rect<double> containerRect = GetContainerRect().GetResolutionRect();
  sf::Rect<double>buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 20, containerRect.Top, 20, 20 );
  fExitButton->SetRect( buttonPos );
  fExitButton->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 40, containerRect.Top, 20, 20 );
  fPinButton->SetRect( buttonPos );
  fPinButton->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left, containerRect.Top, containerRect.Width - 40, 20 );
  fTopBar->SetRect( buttonPos );
  fTopBar->RenderT( windowApp );
  fFrame->RenderGUI( windowApp );
}

FrameUIReturn 
FrameContainer::NewEvent( UIEvent& event )
{
  FrameUIReturn returnEvent;
  switch( event.Type )
    {
    case sf::Event::MouseButtonPressed:
      {
	if( fTopBar->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fTopBar->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eStartMove );
	  }
	if( fExitButton->ContainsPoint( event.GetResolutionCoord() ) )
	  fExitButton->NewEvent( event );
	if( fPinButton->ContainsPoint( event.GetResolutionCoord() ) )
	  fPinButton->NewEvent( event );
      }
      break;
    case sf::Event::MouseButtonReleased:
      {
	if( fExitButton->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fExitButton->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eClosed );
	  }

	if( fPinButton->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fPinButton->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::ePinned );
	  }

	if( fTopBar->GetState() ) // Always Stop moving if mouse up
	  {
	    fTopBar->NewEvent( event );
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
  Rect full = GetContainerRect();
  sf::Rect<double> rect = full.GetResolutionRect();
  configTable.SetI( "posX", static_cast<int>( rect.Left ) );
  configTable.SetI( "posY", static_cast<int>( rect.Top ) );
  configTable.SetI( "sizeX", static_cast<int>( rect.Width ) );
  configTable.SetI( "sizeY", static_cast<int>( rect.Height ) );
  fFrame->SaveConfiguration( configTable );
}

void 
FrameContainer::Resize( const sf::Vector2<double>& size )
{
  Rect newRect = GetContainerRect();
  sf::Vector2<double> position = newRect.GetResolutionCoord();
  newRect.SetFromResolutionRect( sf::Rect<double>( position.x, position.y, size.x, size.y ) );
  SetContainerRect( newRect );
}

void 
FrameContainer::Move( const sf::Vector2<double>& position )
{
  Rect newRect = GetContainerRect();
  sf::Vector2<double> resolution = Coord::GetWindowResolution();
  if( position.x > resolution.x || position.y > resolution.y )
    return;
  newRect.SetFromResolutionCoord( position );
  SetContainerRect( newRect );
}


void 
FrameContainer::SetContainerRect( Rect& containerRect )
{
  fContainerRect = containerRect;
  sf::Rect<double> rect = fContainerRect.GetResolutionRect();
  rect.Top = rect.Top + 20;
  rect.Height = rect.Height - 20;
  Rect frameRect;
  frameRect.SetFromResolutionRect( rect );
  fFrame->SetRect( frameRect );
}

Rect
FrameContainer::GetContainerRect()
{
  return fContainerRect;
}

sf::Vector2<double> 
FrameContainer::GetPos()
{
  return GetContainerRect().GetResolutionCoord();
}

sf::Vector2<double> 
FrameContainer::GetSize()
{
  sf::Rect<double> rect = GetContainerRect().GetResolutionRect();
  return sf::Vector2<double>( rect.Width, rect.Height );
}
