#include <SFML/Window/Event.hpp>

#include <Viewer/UIEvent.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Configuration.hh>
using namespace Viewer;

#include <iostream>
#include <string>
using namespace std;

void
FrameManager::Initialise()
{
  fFocus = -1;
  fMoving = false;
}

void 
FrameManager::Initialise( Configuration& config )
{
  Initialise();
  for( vector< ConfigurationTable* >::iterator iTer = config.GetTableBegin(); iTer != config.GetTableEnd(); iTer++ )
    {
      ConfigurationTable& currentTable = **iTer;
      FrameContainer* currentFrameContainer = new FrameContainer( currentTable );
      fFrameContainers.push_back( currentFrameContainer );
    }
}
  
void 
FrameManager::NewEvent( UIEvent& event )
{
  FrameUIReturn retEvent; // Returned event
  int oldFocus = fFocus;
  switch( event.Type )
    {
// First events that go straight through to Focus
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
      {
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent = fFrameContainers[fFocus]->NewEvent( event );
	break;
      }

// Now events that go straight through to Focus and change the focus   
    case sf::Event::MouseButtonReleased:
      {
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent = fFrameContainers[fFocus]->NewEvent( event );
	fFocus = FindFrame( event.GetResolutionCoord() );
	fMoving = false; // Always release if mouse button up
	break; 
      }

// Now events that change the focus   
    case sf::Event::MouseButtonPressed:
      {
	fFocus = FindFrame( event.GetResolutionCoord() );   
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent = fFrameContainers[fFocus]->NewEvent( event );
	break;
      }

    case sf::Event::MouseMoved:
      {
	sf::Vector2<double> point = event.GetResolutionCoord();
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
    if( fFrameContainers[uFrame]->GetContainerRect().ContainsResolutionPoint( resolutionCoord ) )
      return static_cast<int>( uFrame );
  return -1;
}
