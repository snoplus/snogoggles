#include <SFML/Graphics/Rect.hpp>

#include <Viewer/EventMasterUI.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/RadioCheckBoxes.hh>
#include <Viewer/Selector.hh>
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
	case 4: // GUI Colour Selector
	  GUIColourPalette::gPalette = fGUIColourFactory.New( fGUIColourSelector->GetStringState() );
	  // Notify the GUI textures that they have changed...
	  GUITextureManager::GetInstance().ChangeColourScheme();
	  break;
	case 5: // Event Colour Selector
	  ColourPalette::gPalette = fColourFactory.New( fColourSelector->GetStringState() );
	  break;
	}
      fEvents.pop();
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
  size.Left = 0.8; size.Top = 0.1; size.Width = 0.1; size.Height = 0.05;
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

  size.Top = 0.8; size.Left = 0.0; size.Height = 0.05; size.Width = 0.9;
  fGUIColourSelector = fGUIManager.NewGUI<GUIs::Selector>( size );
  fGUIColourSelector->Initialise( fGUIColourFactory.GetNames() );

  size.Top = 0.7; size.Left = 0.0; size.Height = 0.05; size.Width = 0.9;
  fColourSelector = fGUIManager.NewGUI<GUIs::Selector>( size );
  fColourSelector->Initialise( fColourFactory.GetNames() );
}

void 
EventMasterUI::LoadConfiguration( ConfigurationTable& configTable )
{
  // load current desktop
}

void 
EventMasterUI::RenderGUI( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}

RenderState 
EventMasterUI::GetRenderState()
{
  return RenderState( fSourceRadio->GetEnumState<RenderState::EDataSource>(), fTypeRadio->GetEnumState<RenderState::EDataType>());
}
