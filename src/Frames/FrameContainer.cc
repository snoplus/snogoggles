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
#include <Viewer/TopBarRightButton.hh>
#include <Viewer/IncreaseButton.hh>
#include <Viewer/DecreaseButton.hh>
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
  fTopBarRight = new GUIs::TopBarRightButton( tempPos, 2 );
  fIncreaseButton = new GUIs::IncreaseButton( tempPos, 3 );
  fDecreaseButton = new GUIs::DecreaseButton( tempPos, 4 );

  fFrame->Initialise();
  fTopBar = new GUIs::TopBarButton( tempPos, 5 );
  fTopBar->SetTitle( fFrame->GetName() );
}

void 
FrameContainer::LoadConfiguration( ConfigurationTable& configTable )
{      
  sf::Vector2<double> pos( configTable.GetI( "posX" ), configTable.GetI( "posY" ) );
  sf::Vector2<double> size( configTable.GetI( "sizeX" ), configTable.GetI( "sizeY" ) );
  fPinButton->SetState( configTable.GetI( "pinned" ) );
  Move( pos );
  Resize( size );

  fFrame->LoadConfiguration( configTable );
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
  sf::Rect<double>buttonPos;
  buttonPos = sf::Rect<double>( containerRect.Left, containerRect.Top, containerRect.Width - 100, 20 );
  fTopBar->SetRect( buttonPos );
  fTopBar->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 20, containerRect.Top, 20, 20 );
  fTopBarRight->SetRect( buttonPos );
  fTopBarRight->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 40, containerRect.Top, 20, 20 );
  fExitButton->SetRect( buttonPos );
  fExitButton->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 60, containerRect.Top, 20, 20 );
  fPinButton->SetRect( buttonPos );
  fPinButton->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 80, containerRect.Top, 20, 20 );
  fIncreaseButton->SetRect( buttonPos );
  fIncreaseButton->RenderT( windowApp );

  buttonPos = sf::Rect<double>( containerRect.Left + containerRect.Width - 100, containerRect.Top, 20, 20 );
  fDecreaseButton->SetRect( buttonPos );
  fDecreaseButton->RenderT( windowApp );

  fFrame->RenderGUI( windowApp );
}

FrameUIReturn 
FrameContainer::NewEvent( UIEvent& event )
{
  FrameUIReturn returnEvent;
  switch( event.Type )
    {
    case sf::Event::LostFocus: //No explicit focus for container buttons, so must inform all
      fTopBar->NewEvent( event );
      fTopBarRight->NewEvent( event );
      fExitButton->NewEvent( event );
      fPinButton->NewEvent( event );
      fIncreaseButton->NewEvent( event );
      fDecreaseButton->NewEvent( event );
      break;
    case sf::Event::MouseButtonPressed:
      {
	if( fTopBar->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fTopBar->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eStartMove );
	  }
	if( fTopBarRight->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fTopBarRight->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eStartMove );
	  }
	if( fExitButton->ContainsPoint( event.GetResolutionCoord() ) )
	  fExitButton->NewEvent( event );
	if( fPinButton->ContainsPoint( event.GetResolutionCoord() ) )
	  fPinButton->NewEvent( event );
	if( fIncreaseButton->ContainsPoint( event.GetResolutionCoord() ) )
	  fIncreaseButton->NewEvent( event );
	if( fDecreaseButton->ContainsPoint( event.GetResolutionCoord() ) )
	  fDecreaseButton->NewEvent( event );
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
	if( fIncreaseButton->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fIncreaseButton->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eIncrease );
	  }
	if( fDecreaseButton->ContainsPoint( event.GetResolutionCoord() ) )
	  {
	    fDecreaseButton->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eDecrease );
	  }
	if( fTopBar->GetState() ) // Always Stop moving if mouse up
	  {
	    fTopBar->NewEvent( event );
	    returnEvent = FrameUIReturn( FrameUIReturn::eStopMove );
	  }	
	if( fTopBarRight->GetState() ) // Always Stop moving if mouse up
	  {
	    fTopBarRight->NewEvent( event );
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
  configTable.SetI( "posX", static_cast<int>( rect.Left + 1 ) ); //+1 to allow safer positioning on load
  configTable.SetI( "posY", static_cast<int>( rect.Top + 1 ) );
  configTable.SetI( "sizeX", static_cast<int>( rect.Width + 1 ) );
  configTable.SetI( "sizeY", static_cast<int>( rect.Height + 1 ) );
  configTable.SetI( "pinned", IsPinned() );
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
