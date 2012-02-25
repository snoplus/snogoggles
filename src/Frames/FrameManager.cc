#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <iostream>
using namespace std;

#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/FrameGrid.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Event.hh>
#include <Viewer/FrameMasterUI.hh>
using namespace Viewer;

FrameManager::FrameManager( RectPtr rect,
			    double rightMargin,
			    double bottomMargin )
  : fRect( rect ), fRightMargin( rightMargin ), fBottomMargin( bottomMargin )
{

}

FrameManager::~FrameManager()
{
  delete fgRect;
}

void
FrameManager::NewEvent( const Event& event )
{
  // Check the UI first
  if( fFMUI->ContainsPoint( event.GetPos() ) )
    {
      fFMUI->NewEvent( event );
      ChangeState( eNormal );
    }
  // Else it may affect a frame container
  else
    {
      int oldFocus = fFocus;
      FrameEvent retEvent; // Returned event
      switch( event.Type )
	{
// First events that go straight through to Focus
	case sf::Event::KeyPressed:
	case sf::Event::KeyReleased:
	  {
	    retEvent = DispatchEvent( event, fFocus );
	  }
	  break;	    
// Now events that go straight through to Focus and change the focus
	case sf::Event::MouseButtonReleased:
	  {
	    retEvent = DispatchEvent( event, fFocus );
	    fFocus = FindFrame( event.GetPos() );
	  }
	  break;
// Now events that change the focus
	case sf::Event::MouseButtonPressed:
	  {
	    fFocus = FindFrame( event.GetPos() );
	    retEvent = DispatchEvent( event, fFocus );
	  }
	  break;
	case sf::Event::MouseMoved:
	  {
	    if( fState == eMoving )
	      PositionFrame( event.GetPos(), fFocus, false );
	    else
	      {
		fFocus = FindFrame( event.GetPos() );
		retEvent = DispatchEvent( event, fFocus );
	      }
	  }
	  break;
	}
      // Has the focus changed?
      if( oldFocus != fFocus )
	{
	  // Broadcast a lost focus event
	  ChangeState( eNormal );
	  Event lostFocus( sf::Event::LostFocus );
	  retEvent = DispatchEvent( lostFocus, oldFocus );
	  EventHandler( retEvent );
	  // Minimise the old focus
	  ResizeFrame( FrameGrid::eSmallest, oldFocus );
	  // Maximuse the new focus
	  ResizeFrame( FrameGrid::eLargest, fFocus );
	}
      else
	EventHandler( retEvent );
    }
}

FrameEvent
FrameManager::DispatchEvent( const Event& event, 
			     const int targetFrame )
{
  FrameEvent retEvent;
  if( targetFrame >=0 && targetFrame < fFrameContainers.size() )
    retEvent = fFrameContainers[targetFrame]->NewEvent( event );
  retEvent.fFrameID = targetFrame;
  return retEvent;
}

void 
FrameManager::EventLoop()
{
  // Now pass on to the frames
  fFMUI->EventLoop();
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    (*iTer)->EventLoop();
}

void 
FrameManager::SaveConfiguration( ConfigurationTable& configTable )
{

}

void 
FrameManager::Initialise()
{
  // First create the frame grid
  sf::Rect<double> defaultSize;
  defaultSize.Left = 0.0; defaultSize.Top = 0.0; defaultSize.Width = 1.0 - fRightMargin; defaultSize.Height = 1.0 - fBottomMargin;
  fgRect = new RectPtr( fRect->NewDaughter( defaultSize, Rect::eLocal ) );
  fFrameGrid = new FrameGrid( *fgRect );
  // Then initialise the UI
  defaultSize.Left = 0.0; defaultSize.Top = 1.0 - fBottomMargin; defaultSize.Width = 1.0 - fRightMargin; defaultSize.Height = fBottomMargin;
  RectPtr fmRect( fRect->NewDaughter( defaultSize, Rect::eLocal ) );
  fFMUI = new FrameMasterUI( fmRect, *fgRect, this );
  fFMUI->Initialise();
  // Now set the state
  fFocus = -1;
  fState = eNormal;
}

void 
FrameManager::LoadConfiguration( ConfigurationTable& configTable )
{
  Initialise();
  //for( vector<FrameManager*>::iterator iTer = fFrameManagers.begin(); iTer != fFrameManagers.end(); iTer++ )
    // Need names of tables

}

void 
FrameManager::Render2d( RWWrapper& renderApp, 
			const RenderState& renderState )
{
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    (*iTer)->Render2d( renderApp, renderState );
}

void 
FrameManager::Render3d( RWWrapper& renderApp,
			const RenderState& renderState )
{
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    (*iTer)->Render3d( renderApp, renderState );
}

void 
FrameManager::RenderGUI( RWWrapper& renderApp,
			 const RenderState& renderState )
{
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    (*iTer)->RenderGUI( renderApp, renderState );
  fFMUI->Render( renderApp );
}

void 
FrameManager::EventHandler( const FrameEvent& retEvent )
{
  switch( retEvent.fType )
    {
    case FrameEvent::ePinned:
      break;
    case FrameEvent::eClosed:
      DeleteFrame( retEvent.fFrameID );
      break;
    case FrameEvent::eStartMove:
      {
	ChangeState( eMoving );
	ResizeFrame( FrameGrid::eSmallest, retEvent.fFrameID );
	sf::Rect<double> startRect = fFrameContainers[retEvent.fFrameID]->GetRect()->GetRect( Rect::eResolution );
	fMoveOrigin = sf::Vector2<double>( startRect.Left, startRect.Top );
      }
      break;
    case FrameEvent::eStopMove:
      {
	sf::Rect<double> endRect = fFrameContainers[retEvent.fFrameID]->GetRect()->GetRect( Rect::eResolution );
	sf::Vector2<double> endPos( endRect.Left, endRect.Top );
	PositionFrame( endPos, retEvent.fFrameID, true );
	ChangeState( eNormal );
      }
      break;
    case FrameEvent::eIncrease:
      ResizeFrame( FrameGrid::eLarger, retEvent.fFrameID );
      break;
    case FrameEvent::eDecrease:
      ResizeFrame( FrameGrid::eSmaller, retEvent.fFrameID );
      break;
    }
}

void 
FrameManager::ChangeState( const EState state )
{ 
  fState = state;
}


int 
FrameManager::FindFrame( const sf::Vector2<double>& coord )
{
  int targetFrame = -1;
  for( int iFrame = 0; iFrame < fFrameContainers.size(); iFrame++ )
    if( fFrameContainers[iFrame]->ContainsPoint( coord ) )
      targetFrame = iFrame;
  return targetFrame;
}

void 
FrameManager::NewFrame( Frame* frame )
{
  sf::Rect<double> rect;
  if( fFrameGrid->NewFrame( fFrameContainers.size(), rect ) )
    {
      RectPtr rectPtr( (*fgRect)->NewDaughter( rect, Rect::eLocal ) );
      FrameContainer* newFrame = new FrameContainer( rectPtr );
      newFrame->Initialise( frame );
      fFrameContainers.push_back( newFrame );
    }
}

void 
FrameManager::DeleteFrame( const int targetFrame )
{
  if( targetFrame >= 0 && targetFrame < fFrameContainers.size() )
    fFrameGrid->RemoveFrame( targetFrame, fFrameContainers.size() );
  delete fFrameContainers[targetFrame];
  fFrameContainers.erase( fFrameContainers.begin() + targetFrame );
  fFocus = -1;
  ChangeState( eNormal );
}

void 
FrameManager::PositionFrame( const sf::Vector2<double>& coord,
			     const int targetFrame,
			     bool final )
{ // need final and move temp
  if( targetFrame >= 0 && targetFrame < fFrameContainers.size() )
    {
      // Do not try to move pinned frames
      if( fFrameContainers[targetFrame]->IsPinned() )
	return;
      if( final )
	{
	  sf::Rect<double> rect;
	  if( fFrameGrid->MoveFrame( targetFrame, coord, rect ) )
	    fFrameContainers[targetFrame]->SetRect( rect, Rect::eLocal );
	  else
	    PositionFrame( fMoveOrigin, targetFrame, true );
	}
      else
	{
	  sf::Rect<double> rect = fFrameContainers[targetFrame]->GetRect()->GetRect( Rect::eResolution );
	  rect.Left = coord.x; rect.Top = coord.y;
	  fFrameContainers[targetFrame]->SetRect( rect, Rect::eResolution );
	}
    }
}

void 
FrameManager::ResizeFrame( const FrameGrid::ESize size,
			   const int targetFrame )
{
  if( targetFrame >= 0 && targetFrame < fFrameContainers.size() )
    {
      // Don't minimise or maximise if the frame is pinned
      if( ( size == FrameGrid::eSmallest || size == FrameGrid::eLargest ) && fFrameContainers[targetFrame]->IsPinned() )
	return;
      sf::Rect<double> rect;
      if( fFrameGrid->ResizeFrame( targetFrame, size, rect ) )
	fFrameContainers[targetFrame]->SetRect( rect, Rect::eLocal );
    }
}
