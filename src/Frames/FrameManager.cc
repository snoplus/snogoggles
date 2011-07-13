#include <SFML/Window/Event.hpp>

#include <Viewer/UIEvent.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/MasterUI.hh>
using namespace Viewer;

#include <iostream>
#include <string>
using namespace std;

void
FrameManager::Initialise()
{
  fFocus = -1;
  fMoving = false;
  fCols = 10;
  sf::Vector2<double> resolution = Coord::GetWindowResolution();
  fColSize = resolution.x / fCols;
  fRowSize = fColSize;
  fRows = resolution.y / fRowSize;
  fFrameGrid.resize( fCols, vector<int>( fRows, -1 ) ); 
  fMasterUI = new Frames::MasterUI( this );
  Rect masterUI;
  masterUI.SetFromResolutionRect( sf::Rect<double>( 0.0, fRowSize * fRows, resolution.x, resolution.y - fRowSize * fRows ) );
  fMasterUI->SetRect( masterUI );
}

void 
FrameManager::Initialise( Configuration& config )
{
  Initialise();
  for( vector< ConfigurationTable* >::iterator iTer = config.GetTableBegin(); iTer != config.GetTableEnd(); iTer++ )
    {
      ConfigurationTable& currentTable = **iTer;
      FrameContainer* currentFrameContainer = new FrameContainer();
      currentFrameContainer->Initialise( currentTable );
      fFrameContainers.push_back( currentFrameContainer );
      PositionFrame( fFrameContainers.size() - 1, currentFrameContainer->GetPos() );
    }
}
  
void 
FrameManager::NewEvent( UIEvent& event )
{
// Drop out to MasterUI frame if required FIRST
  if( fMasterUI->ContainsResolutionPoint( event.GetResolutionCoord() ) )
    fMasterUI->NewEvent( event );

  FrameUIReturn retEvent; // Returned event
  int oldFocus = fFocus;
  switch( event.Type )
    {
// First events that go straight through to Focus
    case sf::Event::KeyPressed:
    case sf::Event::KeyReleased:
      {
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent = DispatchEvent( event, fFocus );
	break;
      }

// Now events that go straight through to Focus and change the focus   
    case sf::Event::MouseButtonReleased:
      {
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent  = DispatchEvent( event, fFocus );
	fFocus = FindFrame( event.GetResolutionCoord() );
	break; 
      }

// Now events that change the focus   
    case sf::Event::MouseButtonPressed:
      {
	fFocus = FindFrame( event.GetResolutionCoord() );   
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent = DispatchEvent( event, fFocus );
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
	  retEvent = DispatchEvent( event, fFocus );
	break;
      }
    }
// Focus change
  if( oldFocus != fFocus ) 
    {
      if( oldFocus != -1 ) // Signal lost focus and resize
	{
	  event.Type = sf::Event::LostFocus;
	  fFrameContainers[oldFocus]->NewEvent( event );
	  // Also minimise if not pinned
	  if( !fFrameContainers[oldFocus]->IsPinned() )
	    ResizeFrame( oldFocus, eMinimal );
	}
      if( fFocus != -1 )
	{
	  if( !fFrameContainers[fFocus]->IsPinned() )
	    ResizeFrame( fFocus, eLarger );
	}
    }
  EventHandler( retEvent );
}

FrameUIReturn
FrameManager::DispatchEvent( UIEvent& event, int iFrame )
{
  FrameUIReturn retEvent;
  if( iFrame >=0 && iFrame < fFrameContainers.size() )
    retEvent = fFrameContainers[iFrame]->NewEvent( event );
  retEvent.fFrameID = iFrame;
  return retEvent;
}

void
FrameManager::EventHandler( FrameUIReturn& retEvent )
{
  switch( retEvent.fType )
    {
    case FrameUIReturn::ePinned:
      break;
    case FrameUIReturn::eClosed:
      DeleteFrame( fFocus );
      break;
    case FrameUIReturn::eStartMove:
      if( !fFrameContainers[fFocus]->IsPinned() )
	fMoving = true;
      break;
    case FrameUIReturn::eStopMove:
      fMoving = false;
      PositionFrame( retEvent.fFrameID, fFrameContainers[retEvent.fFrameID]->GetPos() );
      break;
    }
}

void 
FrameManager::RenderGUI( sf::RenderWindow& windowApp )
{
  fMasterUI->RenderGUI( windowApp );
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    fFrameContainers[uFrame]->RenderGUI( windowApp );
}

void
FrameManager::EventLoop()
{
  fMasterUI->EventLoop();
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

void
FrameManager::DeleteFrame( const int iFrame )
{
  if( fFocus == iFrame )
    fFocus = -1;
  delete fFrameContainers[iFrame];
  for( unsigned int uFrame = iFrame; uFrame < fFrameContainers.size() - 1; uFrame++ )
    fFrameContainers[uFrame] = fFrameContainers[uFrame+1];
  fFrameContainers.pop_back();
}

void
FrameManager::PositionFrame( int iFrame, const sf::Vector2<double>& position )
{
  int col = position.x / fColSize;
  int row = position.y / fRowSize;
  sf::Vector2<double> gridPos( col * fColSize, row * fRowSize );
  fFrameContainers[iFrame]->Move( gridPos );
  (fFrameGrid[col])[row] = iFrame;
}

void
FrameManager::ResizeFrame( int iFrame, ESize size )
{
  switch( size )
    {
    case eMinimal:
      fFrameContainers[iFrame]->Resize( sf::Vector2<double>( fColSize, fRowSize ) );
      break;
    case eLarger:
      {
	double aspectRatio = 1.0;//fFrameContainers[iFrame]->GetAspectRatio();
	sf::Vector2<double> currentSize = fFrameContainers[iFrame]->GetSize();
	int rowSize = currentSize.y / fRowSize;
	rowSize++;
	int colSize = aspectRatio * rowSize;
	fFrameContainers[iFrame]->Resize( sf::Vector2<double>( colSize * fColSize, rowSize * fRowSize ) );
	break;
      }
    case eSmaller:
      {
	double aspectRatio = 1.0;//fFrameContainers[iFrame]->GetAspectRatio();
	sf::Vector2<double> currentSize = fFrameContainers[iFrame]->GetSize();
	int rowSize = currentSize.y / fRowSize;
	rowSize--;
	int colSize = aspectRatio * rowSize;
	fFrameContainers[iFrame]->Resize( sf::Vector2<double>( colSize * fColSize, rowSize * fRowSize ) );
	break;
      }
    }
}

void 
FrameManager::NewFrame( const std::string& type )
{
  FrameContainer* currentFrameContainer = new FrameContainer();
  currentFrameContainer->Initialise( type );
  fFrameContainers.push_back( currentFrameContainer );
  PositionFrame( fFrameContainers.size() - 1, sf::Vector2<double>( 0.0, 0.0 ) );
  ResizeFrame( fFrameContainers.size() - 1, eMinimal );
}
