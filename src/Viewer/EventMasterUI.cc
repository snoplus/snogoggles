#include <SFML/Graphics/Rect.hpp>

#include <Viewer/EventMasterUI.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/RadioCheckBoxes.hh>
#include <Viewer/Selector.hh>
#include <Viewer/ScalingBar.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/Event.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/RIDS/RIDS.hh>
using namespace Viewer;

EventMasterUI::EventMasterUI( RectPtr rect )
  : fRect( rect ), fGUIManager( rect )
{

}

EventMasterUI::~EventMasterUI()
{
  fRefreshSelector = NULL; // GUI Manager deletes these
  fTypeRadio = NULL;
  fSourceRadio = NULL;
  fScalingBar = NULL;
}

void 
EventMasterUI::NewEvent( const Event& event )
{
  DataStore& events = DataStore::GetInstance();
  if( event.Type == sf::Event::KeyPressed )
    {
      if( event.Key.Code == sf::Keyboard::Right )
        events.Next();
      else if( event.Key.Code == sf::Keyboard::Left )
        events.Prev();
    }
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
EventMasterUI::EventLoop()
{
  DataStore& events = DataStore::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Next EV
          events.Next();
          break;
        case 1: // Prev EV
          events.Prev();
          break;
        case 2: // Event type change 
        case 3: // Event type change 
          // Must reset the scaling
          fCurrentRenderState.ChangeState( fSourceRadio->GetEnumState<RIDS::EDataSource>(), fTypeRadio->GetEnumState<RIDS::EDataType>() );
          fScalingBar->Reset();
          break;
        case 5: // New Scaling
          fCurrentRenderState.ChangeScaling( fScalingBar->GetMin(), fScalingBar->GetMax() );
          break;
        }
      fEvents.pop();
    }
  switch( fRefreshSelector->GetState() )
    {
    case 0: // Stopped
      break;
    case 1: // Instant refresh
      events.Latest();
      break;
    case 2: // 0.5 second
      if( fClock.GetElapsedTime().AsSeconds() > 0.5 )
        {
          events.Next();
          fClock.Restart();
        }
    case 3: // 2 seconds
      if( fClock.GetElapsedTime().AsSeconds() > 2.0 )
        {
          events.Next();
          fClock.Restart();
        }
    }
}

void 
EventMasterUI::Initialise()
{
  sf::Rect<double> size;
  size.Left = 0.8; size.Top = 0.0; size.Width = 0.1; size.Height = 0.05;
  GUIs::GUIImageButton* nextEVGUI = fGUIManager.NewGUI<GUIs::GUIImageButton>( size );
  nextEVGUI->Initialise( eIncrease );

  size.Left = 0.1;
  GUIs::GUIImageButton* prevEVGUI = fGUIManager.NewGUI<GUIs::GUIImageButton>( size );
  prevEVGUI->Initialise( eDecrease );

  size.Top = 0.2; size.Height = 0.25; size.Width = 0.8;
  fSourceRadio = fGUIManager.NewGUI<GUIs::RadioCheckBoxes>( size );
  fSourceRadio->Initialise( RenderState::GetSourceStrings() );

  size.Top = 0.5; size.Height = 0.2; size.Width = 0.8;
  fTypeRadio = fGUIManager.NewGUI<GUIs::RadioCheckBoxes>( size );
  fTypeRadio->Initialise( RenderState::GetTypeStrings() );

  size.Left = 0.1; size.Top = 0.1; size.Width = 0.8; size.Height = 0.05;
  fRefreshSelector = fGUIManager.NewGUI<GUIs::Selector>( size );
  vector<string> refreshStrings;
  refreshStrings.push_back( "Stop" ); refreshStrings.push_back( "Instant" ); refreshStrings.push_back( "1/2 sec" ); refreshStrings.push_back( "2 sec" );
  fRefreshSelector->Initialise( refreshStrings );

  size.Left = 0.1; size.Top = 0.7; size.Width = 0.8; size.Height = 0.05;
  fScalingBar = fGUIManager.NewGUI<GUIs::ScalingBar>( size );
}

void 
EventMasterUI::LoadConfiguration( const ConfigurationTable* configTable )
{
  fSourceRadio->SetState( configTable->GetI( "sourceType" ) );
  fTypeRadio->SetState( configTable->GetI( "dataType" ) );
  fRefreshSelector->SetState( configTable->GetI( "refreshState" ) );
  fCurrentRenderState.ChangeState( fSourceRadio->GetEnumState<RIDS::EDataSource>(), fTypeRadio->GetEnumState<RIDS::EDataType>() );
}

void 
EventMasterUI::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "sourceType", fSourceRadio->GetState() );
  configTable->SetI( "dataType", fTypeRadio->GetState() );
  configTable->SetI( "refreshState", fRefreshSelector->GetState() );
}

void 
EventMasterUI::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}

RenderState 
EventMasterUI::GetRenderState()
{
  return fCurrentRenderState; 
}
