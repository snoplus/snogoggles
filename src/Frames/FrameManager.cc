#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/Rect.hh>
#include <Viewer/Event.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

FrameManager::FrameManager( RectPtr rect )
  : fRect( rect ), fFrameFactory( rect )
{
  const ConfigurationTable* guiConfig = GUIProperties::GetInstance().GetConfiguration( "FrameManager" );
  sf::Rect<double> frameRect( guiConfig->GetD( "x" ), guiConfig->GetD( "y" ), guiConfig->GetD( "width" ), guiConfig->GetD( "height" ) );
  fRect->SetRect( frameRect, Rect::eLocal );
}

FrameManager::~FrameManager()
{
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    delete *iTer;
}

void
FrameManager::NewEvent( const Event& event )
{
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
  for( vector<FrameContainer*>::iterator iTer = fFrameContainers.begin(); iTer != fFrameContainers.end(); iTer++ )
    (*iTer)->EventLoop();
}

void 
FrameManager::PreInitialise( const ConfigurationTable* configTable )
{
  // Now set the state
  fFocus = -1;
  fState = eNormal;
  if( configTable != NULL )
    {
      for( unsigned int uFrame = 0; uFrame < configTable->GetNumTables(); uFrame++ )
        {
          stringstream tableName;
          tableName << "Frame" << uFrame;
          const ConfigurationTable* frameConfig = configTable->GetTable( tableName.str() );
          NewFrame( uFrame, fFrameFactory.New( frameConfig->GetS( "type" ) ), frameConfig );
        }
    }
}

void 
FrameManager::PostInitialise( const ConfigurationTable* configTable )
{
  if( configTable != NULL )
    {
      for( unsigned int uFrame = 0; uFrame < configTable->GetNumTables(); uFrame++ )
        {
          stringstream tableName;
          tableName << "Frame" << uFrame;
          const ConfigurationTable* frameConfig = configTable->GetTable( tableName.str() );
          fFrameContainers[uFrame]->PostInitialise( frameConfig );
        }
    }
}

void 
FrameManager::SaveConfiguration( ConfigurationTable* configTable )
{
  // Now save the frame information
  for( unsigned int uFrame = 0; uFrame < fFrameContainers.size(); uFrame++ )
    {
      stringstream tableName;
      tableName << "Frame" << uFrame;
      ConfigurationTable* currentConfig = configTable->NewTable( tableName.str() );
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
  RectPtr rectPtr( fRect->NewDaughter( rect, Rect::eResolution ) );
  FrameContainer* newFrame = new FrameContainer( rectPtr );
  newFrame->SetFrame( frame );
  newFrame->PreInitialise( NULL );
  newFrame->PostInitialise( NULL );
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
                        const ConfigurationTable* configTable )
{
  sf::Rect<double> rect;
  RectPtr rectPtr( fRect->NewDaughter( rect, Rect::eLocal ) );
  FrameContainer* newFrame = new FrameContainer( rectPtr );
  newFrame->SetFrame( frame );
  newFrame->PreInitialise( configTable );
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
