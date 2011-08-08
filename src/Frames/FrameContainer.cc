#include <SFML/Window/Event.hpp>

#include <string>
#include <iostream>
using namespace std;

#include <Viewer/FrameContainer.hh>
#include <Viewer/Frame.hh>
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

  fFrame->Initialise();
  fTopBar.SetTitle( fFrame->GetName() );
}

void 
FrameContainer::LoadConfiguration( ConfigurationTable& configTable )
{      
  sf::Vector2<double> pos( configTable.GetI( "posX" ), configTable.GetI( "posY" ) );
  sf::Vector2<double> size( configTable.GetI( "sizeX" ), configTable.GetI( "sizeY" ) );
  Move( pos );
  Resize( size );

  fFrame->LoadConfiguration( configTable );
} 

FrameContainer::~FrameContainer()
{
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
  fTopBar.SetRect( sf::Rect<double>( containerRect.Left, containerRect.Top, containerRect.Width, 20 ) );
  fTopBar.RenderT( windowApp );
  fFrame->RenderGUI( windowApp );
}

FrameUIReturn 
FrameContainer::NewEvent( UIEvent& event )
{
  FrameUIReturn returnEvent;
  switch( event.Type )
    {
    case sf::Event::LostFocus: //No explicit focus for container buttons, so must inform all
      fTopBar.NewEvent( event );
      break;
    case sf::Event::MouseMoved:
    case sf::Event::MouseButtonReleased:
    case sf::Event::MouseButtonPressed:
	if( fTopBar.ContainsPoint( event.GetResolutionCoord() ) )
	  returnEvent = fTopBar.NewEvent( event );
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
