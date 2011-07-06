#include <SFML/Window/Event.hpp>

#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/FrameCoord.hh>
#include <Viewer/Configuration.hh>
using namespace Viewer;

#include <iostream>
#include <string>
using namespace std;

void 
FrameManager::Initialise( Configuration& config )
{
  for( vector< ConfigurationTable* >::iterator iTer = config.GetTableBegin(); iTer != config.GetTableEnd(); iTer++ )
    {
      ConfigurationTable& currentTable = **iTer;
      FrameContainer* currentFrameContainer = new FrameContainer( currentTable );
      fFrameContainers.push_back( currentFrameContainer );
    }
  fFocus = -1;
  fMoving = false;
}
  
void 
FrameManager::NewEvent( sf::Event& event )
{
  FrameUIReturn retEvent; // Returned event
  sf::Vector2<double> point;
  int oldFocus = fFocus;
  switch( event.Type )
    {
// First events that go straight through to Focus
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
      if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	retEvent = fFrameContainers[fFocus]->NewEvent( event );
      break;

// Now events that go straight through to Focus and change the focus   
    case sf::Event::MouseButtonReleased:
      if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	retEvent = fFrameContainers[fFocus]->NewEvent( event );
      point = sf::Vector2<double>( event.MouseButton.X, event.MouseButton.Y );
      point = FrameCoord::WindowToResolutionCoord( point );
      fFocus = FindFrame( point );
      fMoving = false; // Always release if mouse button up
      if( fFocus == oldFocus ) break; // Drop through if affects something new

// Now events that change the focus   
    case sf::Event::MouseButtonPressed:
      point = sf::Vector2<double>( event.MouseButton.X, event.MouseButton.Y );
      point = FrameCoord::WindowToResolutionCoord( point );
      fFocus = FindFrame( point );   
      if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	retEvent = fFrameContainers[fFocus]->NewEvent( event );
      break;
    case sf::Event::MouseMoved:
      point = sf::Vector2<double>( event.MouseMove.X, event.MouseMove.Y );
      point = FrameCoord::WindowToResolutionCoord( point );
      if( fMoving )
	{
	  fFrameContainers[fFocus]->Move( point );
	  break;
	}
      fFocus = FindFrame( point );
      if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	retEvent = fFrameContainers[fFocus]->NewEvent( event );
      break;
    }
  if( retEvent.fType == FrameUIReturn::eStartMove )
    fMoving = true;
  if( retEvent.fType == FrameUIReturn::eStopMove )
    fMoving = false;
  // Temp below
  if( fFocus != oldFocus && fFocus != -1 ) // Focus has changed to a new frame
    {
      sf::Vector2<double> size( 400, 200 ); //No c++0x yet...
      fFrameContainers[fFocus]->Resize( size );
    }
  if( fFocus != oldFocus && oldFocus != -1 ) // Focus has changed thus Minimise old frame
    {
      sf::Vector2<double> size( 100, 50 ); //No c++0x yet...
      if( fFrameContainers[oldFocus]->IsPinned() == false )
	fFrameContainers[oldFocus]->Resize( size );
    }    
}

void 
FrameManager::RenderGUI( sf::RenderWindow& windowApp )
{
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    fFrameContainers[uFrame]->RenderGUI( windowApp );
}

void
FrameManager::EventLoop()
{
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    fFrameContainers[uFrame]->EventLoop();
}

void 
FrameManager::Render2d( sf::RenderWindow& windowApp )
{
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    fFrameContainers[uFrame]->Render2d( windowApp );
}

void 
FrameManager::Render3d()
{
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    fFrameContainers[uFrame]->Render3d();
}
  
void 
FrameManager::SaveConfiguration( Configuration& config )
{
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    {
      ConfigurationTable& configTable = *config.NewTable( "Frame" );
      fFrameContainers[uFrame]->SaveConfiguration( configTable );
    }
}

int 
FrameManager::FindFrame( const sf::Vector2<double>& resolutionCoord )
{
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    if( fFrameContainers[uFrame]->GetContainerCoord().ContainsPoint( resolutionCoord ) )
      return static_cast<int>( uFrame );
  return -1;
}
