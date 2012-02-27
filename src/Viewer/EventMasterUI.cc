#include <SFML/Graphics/Rect.hpp>

#include <Viewer/EventMasterUI.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/RadioCheckBoxes.hh>
#include <Viewer/Selector.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/EventData.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/Event.hh>
using namespace Viewer;

EventMasterUI::EventMasterUI( RectPtr rect )
  : fRect( rect ), fGUIManager( rect )
{

}

void 
EventMasterUI::NewEvent( const Event& event )
{
  EventData& events = EventData::GetInstance();
  if( event.Type == sf::Event::KeyPressed )
    {
      if( event.Key.Code == sf::Keyboard::Right )
	events.NextEV();
      else if( event.Key.Code == sf::Keyboard::Left )
	events.PreviousEV();
    }
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
EventMasterUI::EventLoop()
{
  EventData& events = EventData::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
	{
	case 0: // Next EV
	  events.NextEV();
	  break;
	case 1: // Prev EV
	  events.PreviousEV();
	  break;
	}
      fEvents.pop();
    }
  // If continuous event switching then...
  if( fContinuousBox->GetState() )
    {
      switch( fRefreshSelector->GetState() )
	{
	case 0: // Instant refresh
	  events.NextEV();
	  break;
	case 1: // 1 second
	  if( fClock.GetElapsedTime().AsSeconds() > 1.0 )
	    {
	      events.NextEV();
	      fClock.Restart();
	    }
	case 2: // 5 seconds
	  if( fClock.GetElapsedTime().AsSeconds() > 5.0 )
	    {
	      events.NextEV();
	      fClock.Restart();
	    }
	}
    }
}

void 
EventMasterUI::SaveConfiguration( ConfigurationTable& configTable )
{
  // Just save current desktop
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
  refreshStrings.push_back( "Instant" ); refreshStrings.push_back( "1 sec" ); refreshStrings.push_back( "5 sec" );
  fRefreshSelector->Initialise( refreshStrings );

  size.Left = 0.1; size.Top = 0.05; size.Width = 0.8; size.Height = 0.05;
  fContinuousBox = fGUIManager.NewGUI<GUIs::CheckBoxLabel>( size );
  fContinuousBox->SetLabel( "Continuous" );
}

void 
EventMasterUI::LoadConfiguration( ConfigurationTable& configTable )
{
  // load current desktop
}

void 
EventMasterUI::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}

RenderState 
EventMasterUI::GetRenderState()
{
  return RenderState( fSourceRadio->GetEnumState<RenderState::EDataSource>(), fTypeRadio->GetEnumState<RenderState::EDataType>());
}
