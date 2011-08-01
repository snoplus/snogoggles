#include <SFML/Window/Event.hpp>

#include <Viewer/UIEvent.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/MasterUI.hh>
using namespace Viewer;

#include <iostream>
#include <string>
using namespace std;

const int kMinFrameWidth = 140; // Minimum frame width 4*20 buttons + 2*20 ends + 20 bar
const int kMasterUIHeight = 80; 

void
FrameManager::Initialise()
{
  fFocus = -1;
  fMoving = false;
  sf::Vector2<double> resolution = Coord::GetWindowResolution();
  fCols = resolution.x / kMinFrameWidth;
  fColSize = resolution.x / fCols;
  fRowSize = fColSize;
  fRows = ( resolution.y - kMasterUIHeight ) / fRowSize;
  fFrameGrid.resize( fCols, vector<int>( fRows, -2 ) ); 
  fMasterUI = new Frames::MasterUI( this );
  Rect masterUI;
  masterUI.SetFromResolutionRect( sf::Rect<double>( 0.0, resolution.y - kMasterUIHeight, resolution.x, kMasterUIHeight ) );
  fMasterUI->SetRect( masterUI );
  CalculateGrid();
  fMoveStart = sf::Vector2<double>( 0.0, 0.0 );
}

void 
FrameManager::LoadConfiguration( Configuration& config )
{
  for( vector< ConfigurationTable* >::iterator iTer = config.GetTableBegin(); iTer != config.GetTableEnd(); iTer++ )
    {
      ConfigurationTable& currentTable = **iTer;
      FrameContainer* currentFrameContainer = new FrameContainer();
      currentFrameContainer->Initialise( currentTable.GetS( "type" ) );
      currentFrameContainer->LoadConfiguration( currentTable );
      fFrameContainers.push_back( currentFrameContainer );
      PositionFrame( fFrameContainers.size() - 1, currentFrameContainer->GetPos() );
    }
  CalculateGrid();
}
  
void 
FrameManager::NewEvent( UIEvent& event )
{
// Drop out to MasterUI frame if required FIRST
  if( fMasterUI->ContainsResolutionPoint( event.GetResolutionCoord() ) )
    fMasterUI->NewEvent( event );
  else
    {
      UIEvent lostFocus = event;
      lostFocus.Type = sf::Event::LostFocus;
      fMasterUI->NewEvent( lostFocus );
    }

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
	    fFrameContainers[fFocus]->Move( point - fMoveOffset );
	    break;
	  }
	fFocus = FindFrame( point );
	if( fFocus >= 0 && fFocus < fFrameContainers.size() )
	  retEvent = DispatchEvent( event, fFocus );
	break;
      }
    }
  EventHandler( retEvent, event );
// Focus change
  if( oldFocus != fFocus && retEvent.fType != FrameUIReturn::eClosed ) 
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
	    ResizeFrame( fFocus, eLargest );
	}
    }
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
FrameManager::EventHandler( FrameUIReturn& retEvent, UIEvent& event )
{
  switch( retEvent.fType )
    {
    case FrameUIReturn::ePinned:
      break;
    case FrameUIReturn::eClosed:
      DeleteFrame( fFocus );
      fFocus = -1;
      break;
    case FrameUIReturn::eStartMove:
      if( !fFrameContainers[fFocus]->IsPinned() )
	{
	  fMoving = true;
	  fMoveOffset = event.GetResolutionCoord() - fFrameContainers[fFocus]->GetPos();
	  fMoveStart = fFrameContainers[fFocus]->GetPos();
	  ResizeFrame( retEvent.fFrameID, eMinimal );
	}
      break;
    case FrameUIReturn::eStopMove:
      fMoving = false;
      PositionFrame( retEvent.fFrameID, fFrameContainers[retEvent.fFrameID]->GetPos() );
      break;
    case FrameUIReturn::eIncrease:
      ResizeFrame( retEvent.fFrameID, eLarger );
      break;
    case FrameUIReturn::eDecrease:
      ResizeFrame( retEvent.fFrameID, eSmaller );
      break;
    }
}

void 
FrameManager::RenderGUI( sf::RenderWindow& windowApp )
{
  fMasterUI->RenderGUI( windowApp );
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    fFrameContainers[uFrame]->RenderGUI( windowApp );
  //DrawGrid( windowApp );
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
FrameManager::NewFrame( const std::string& type )
{
  FrameContainer* currentFrameContainer = new FrameContainer();
  currentFrameContainer->Initialise( type );
  fFrameContainers.push_back( currentFrameContainer );
  const int frameID = fFrameContainers.size() - 1;
  // Position new frame
  for( int iRow = 0; iRow < fRows; iRow++ )
    for( int iCol = 0; iCol < fCols; iCol++ )
      if( CheckPosition( frameID, iRow, iCol, 1, 1 ) )
	{
	  ResizeFrame( frameID, eMinimal );
	  PositionFrame( frameID, sf::Vector2<double>( iCol * fColSize, iRow * fRowSize ) );
	  return;
	}
  // If get here then frame cannot be placed, so delete it
  DeleteFrame( frameID );
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
  CalculateGrid();
}

void
FrameManager::PositionFrame( int iFrame, const sf::Vector2<double>& position )
{
  int col = position.x / fColSize;
  int row = position.y / fRowSize;
  sf::Vector2<double> currentSize = fFrameContainers[iFrame]->GetSize();
  int colSize = currentSize.x / fColSize;
  int rowSize = currentSize.y / fRowSize;
  if( !CheckPosition( iFrame, row, col, rowSize, colSize ) )
    {
      fFrameContainers[iFrame]->Move( fMoveStart );
      return;
    }
  sf::Vector2<double> gridPos( col * fColSize, row * fRowSize );
  fFrameContainers[iFrame]->Move( gridPos );
  CalculateGrid();
}

void
FrameManager::ResizeFrame( int iFrame, ESize size )
{
  sf::Vector2<double> position = fFrameContainers[iFrame]->GetPos();
  int col = position.x / fColSize;
  int row = position.y / fRowSize;
  switch( size )
    {
    case eMinimal:
      fFrameContainers[iFrame]->Resize( sf::Vector2<double>( fColSize, fRowSize ) );
      break;
    case eLargest:
      {
	double aspectRatio = fFrameContainers[iFrame]->GetAspectRatio();
	sf::Vector2<double> currentSize = fFrameContainers[iFrame]->GetSize();
	int rowSize = currentSize.y / fRowSize;
	int colSize = aspectRatio * rowSize;
	while( CheckPosition( iFrame, row, col, rowSize, colSize ) )
	  {
	    rowSize++;
	    colSize = aspectRatio * rowSize;
	  }
	rowSize--;
	colSize = aspectRatio * rowSize;
	fFrameContainers[iFrame]->Resize( sf::Vector2<double>( colSize * fColSize, rowSize * fRowSize ) );	
	break;
      }
    case eLarger:
      {
	double aspectRatio = fFrameContainers[iFrame]->GetAspectRatio();
	sf::Vector2<double> currentSize = fFrameContainers[iFrame]->GetSize();
	int rowSize = currentSize.y / fRowSize;
	rowSize++;
	int colSize = aspectRatio * rowSize;
	if( CheckPosition( iFrame, row, col, rowSize, colSize ) )
	  fFrameContainers[iFrame]->Resize( sf::Vector2<double>( colSize * fColSize, rowSize * fRowSize ) );
	break;
      }
    case eSmaller:
      {
	double aspectRatio = fFrameContainers[iFrame]->GetAspectRatio();
	sf::Vector2<double> currentSize = fFrameContainers[iFrame]->GetSize();
	int rowSize = currentSize.y / fRowSize;
	rowSize--;
	int colSize = aspectRatio * rowSize;
	if( CheckPosition( iFrame, row, col, rowSize, colSize ) )
	  fFrameContainers[iFrame]->Resize( sf::Vector2<double>( colSize * fColSize, rowSize * fRowSize ) );
	break;
      }
    }
  CalculateGrid();
}

bool 
FrameManager::CheckPosition( int iFrame, int row, int col, int rowSize, int colSize )
{
  if( row + rowSize > fRows || col + colSize > fCols || rowSize < 1 || colSize < 1 )
    return false;

  for( int iCol = col; iCol < col + colSize; iCol++ )
    for( int iRow = row; iRow < row + rowSize; iRow++ )
      {
	if( (fFrameGrid[iCol])[iRow] != iFrame && (fFrameGrid[iCol])[iRow] != -1 )
	  return false;
      }

  return true;
}

void
FrameManager::CalculateGrid()
{
  // Reset the grid
  for( int iCol = 0; iCol < fCols; iCol++ )
    for( int iRow = 0; iRow < fRows; iRow++ )
      (fFrameGrid[iCol])[iRow] = -1;

  // Fill the grid
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    {
      sf::Vector2<double> framePos = fFrameContainers[uFrame]->GetPos();
      sf::Vector2<double> frameSize = fFrameContainers[uFrame]->GetSize();
      int cols = frameSize.x / fColSize;
      int rows = frameSize.y / fRowSize;
      int col = framePos.x / fColSize;
      int row = framePos.y / fRowSize;
      for( int iCol = col; iCol < col + cols; iCol++ )
	for( int iRow = row; iRow < row + rows; iRow++ )
	  (fFrameGrid[iCol])[iRow] = uFrame;
    }
}

#include <SFML/Graphics.hpp>

void
FrameManager::DrawGrid( sf::RenderWindow& windowApp )
{
  stringstream text;
  for( int iCol = 0; iCol < fCols; iCol++ )
    for( int iRow = 0; iRow < fRows; iRow++ )
      {
	text.str("");
	text << (fFrameGrid[iCol])[iRow];
	sf::Text label( text.str() );
	label.SetColor( sf::Color( 0, 0, 0 ) );
	label.SetPosition( iCol * fColSize, iRow * fRowSize );
	windowApp.Draw( label );
      }
  return;
  
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    {
      text.str("");
      text << uFrame;
      sf::Text label( text.str() );
      label.SetColor( sf::Color( 0, 0, 0 ) );
      label.SetPosition( fFrameContainers[uFrame]->GetPos().x, fFrameContainers[uFrame]->GetPos().y );
      windowApp.Draw( label );
    }
}
