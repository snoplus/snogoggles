#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Event.hh>
#include <Viewer/FrameMasterUI.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

FrameManager::FrameManager( RectPtr rect,
			    double rightMargin,
			    double bottomMargin )
  : fRect( rect ), fRightMargin( rightMargin ), fBottomMargin( bottomMargin ), fFrameFactory( rect )
{

}

FrameManager::~FrameManager()
{
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    delete *iTer;
  delete fgRect;
  delete fFMUI;
}

void
FrameManager::NewEvent( const Event& event )
{
  if( fFMUI->ContainsPoint( event.GetPos() ) ) // TO REMOVE with panels
    fFMUI->NewEvent( event ); // TO REMOVE with panels

  int oldFocus = fFocus;
  FrameEvent eventReturned;
  switch( fState )
    {
    case eNormal: // Normal state just dispatch events to the frames
      switch( event.Type )
        {
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
          eventReturned = SendEvent( fFocus, event );
          break;
        case sf::Event::LostFocus:
          fFocus = -1;
          break;
        case sf::Event::MouseButtonReleased:
          eventReturned = SendEvent( fFocus, event );
          fFocus = FindFrame( event.GetPos() );
          break;
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseMoved:
          fFocus = FindFrame( event.GetPos() );
          eventReturned = SendEvent( fFocus, event );
          break;
        }
      break;
    case eMoving: // Move the frame
    case eResizing: // Resize the frame
      switch( event.Type )
        {
        case sf::Event::LostFocus: // Nothing to do but send the event and change the state to normal
        case sf::Event::MouseButtonReleased:
          eventReturned = SendEvent( fFocus, event );
          fState = eNormal;
          fFocus = -1;
          break;
        case sf::Event::MouseMoved: // Move and resize the frame
          UpdateFrameRect( fFocus, event.GetPos() );
          break;
        }
      break;
    }
  EventHandler( eventReturned );
  if( oldFocus != fFocus )
    {
      Event lostFocusEvent( sf::Event::LostFocus );
      eventReturned = SendEvent( oldFocus, lostFocusEvent );
      EventHandler( eventReturned );
    }
}

FrameEvent
FrameManager::SendEvent( const int targetFrame,
                         const Event& event )
{
  FrameEvent retEvent;
  if( targetFrame >=0 && targetFrame < fFrameContainers.size() )
    retEvent = fFrameContainers[targetFrame]->NewEvent( event );
  retEvent.fFrameID = targetFrame;
  retEvent.fPos = event.GetPos();
  return retEvent;
}

void
FrameManager::EventHandler( const FrameEvent& eventReturned )
{
  switch( eventReturned.fType )
    {
    case FrameEvent::eClosed:
      DeleteFrame( eventReturned.fFrameID );
      break;
    case FrameEvent::eStartMove:
      fState = eMoving;
      fPressPosition = eventReturned.fPos;
      fPressOffset.x = fPressPosition.x - fFrameContainers[eventReturned.fFrameID]->GetRect( Rect::eResolution ).Left;
      fPressOffset.y = fPressPosition.y - fFrameContainers[eventReturned.fFrameID]->GetRect( Rect::eResolution ).Top;
      break;
    case FrameEvent::eStartResize:
      fState = eResizing;
      fPressPosition = eventReturned.fPos;
      fPressOffset.x = fPressPosition.x - fFrameContainers[eventReturned.fFrameID]->GetRect( Rect::eResolution ).Left;
      fPressOffset.y = fPressPosition.y - fFrameContainers[eventReturned.fFrameID]->GetRect( Rect::eResolution ).Top;
      break;
    case FrameEvent::eStopMove:
    case FrameEvent::eStopResize:
      fState = eNormal;
      fFocus = -1;
      break;
    }
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
FrameManager::Initialise()
{
  // First create the frame grid
  sf::Rect<double> defaultSize;
  defaultSize.Left = 0.0; defaultSize.Top = 0.0; defaultSize.Width = 1.0 - fRightMargin; defaultSize.Height = 1.0 - fBottomMargin;
  fgRect = new RectPtr( fRect->NewDaughter( defaultSize, Rect::eLocal ) );
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
  // Now load the frames
  try
    {
      unsigned int uFrame = 0;
      while( true ) // throws to exit
        {
          stringstream tableName;
          tableName << "Frame" << uFrame;
          ConfigurationTable& currentConfig = *configTable.GetTable( tableName.str() );
          string type = currentConfig.GetS( "type" );
          NewFrame( uFrame, fFrameFactory.New( type ), currentConfig );
          uFrame++;
        }
    }
  catch( ConfigurationTable::NoTableError& e )
    {
      // No more tables to load...
    }
}

void 
FrameManager::SaveConfiguration( ConfigurationTable& configTable )
{
  // Now save the frame information
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    {
      stringstream tableName;
      tableName << "Frame" << uFrame;
      ConfigurationTable& currentConfig = *configTable.NewTable( tableName.str() );
      fFrameContainers[uFrame]->SaveConfiguration( currentConfig );
    }
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
  sf::Rect<double> rect( 0.0, 1.0, 121.0, 121.0 );
  RectPtr rectPtr( (*fgRect)->NewDaughter( rect, Rect::eResolution ) );
  FrameContainer* newFrame = new FrameContainer( rectPtr );
  newFrame->Initialise( frame );
  fFrameContainers.push_back( newFrame );
  int frameID = fFrameContainers.size() - 1;
  for( double x = 0.0; x < fRect->GetRect( Rect::eResolution ).Width; x += 1.0 )
    {
      rect.Left = x;
      if( UpdateFrameRect( frameID, rect ) )
        return;
    }
  // If we get here, must delete frame
  DeleteFrame( frameID );
}

void
FrameManager::NewFrame( unsigned int uFrame,
                        Frame* frame,
                        ConfigurationTable& configTable )
{
  sf::Rect<double> rect;
  RectPtr rectPtr( (*fgRect)->NewDaughter( rect, Rect::eLocal ) );
  FrameContainer* newFrame = new FrameContainer( rectPtr );
  newFrame->Initialise( frame );
  newFrame->LoadConfiguration( configTable );
  fFrameContainers.push_back( newFrame );
}

void 
FrameManager::DeleteFrame( const int targetFrame )
{
  delete fFrameContainers[targetFrame];
  fFrameContainers.erase( fFrameContainers.begin() + targetFrame );
  fFocus = -1;
  fState = eNormal;
}

bool
FrameManager::UpdateFrameRect( const int targetFrame,
                               sf::Rect<double> newRect )
{
  // First check new rect is contained within the frame area
  if( !fRect->ContainsRect( newRect, Rect::eResolution ) ) 
    return false;
  // Now check it is above the minimum width, PHIL improve
  if( newRect.Width < 120.0 )
    return false;
  // Now check it doesn't overlap any other frame
  for( unsigned int iFrame = 0; iFrame < fFrameContainers.size(); iFrame++ )
    {
      if( iFrame == targetFrame )
        continue;
      if( fFrameContainers[iFrame]->Overlaps( newRect ) )
        return false;
    }
  // Great, update the frame and return true
  fFrameContainers[targetFrame]->SetRect( newRect, Rect::eResolution );
  return true;
}

void
FrameManager::UpdateFrameRect( const int targetFrame,
                               sf::Vector2<double> currentPosition )
{
  sf::Rect<double> currentRect = fFrameContainers[targetFrame]->GetRect( Rect::eResolution );
  switch( fState )
    {
    case eMoving:
      currentPosition -= fPressOffset;
      currentRect.Left = currentPosition.x;
      currentRect.Top = currentPosition.y;
      UpdateFrameRect( targetFrame, currentRect );
      break;
    case eResizing:
      currentRect.Width = currentPosition.x - fPressPosition.x + fPressOffset.x;
      currentRect.Height = currentRect.Width * fFrameContainers[targetFrame]->GetAspectRatio();
      UpdateFrameRect( targetFrame, currentRect );
      break;
    }
}
