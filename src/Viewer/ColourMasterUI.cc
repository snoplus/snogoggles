#include <SFML/Graphics/Rect.hpp>

#include <Viewer/ColourMasterUI.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/RadioCheckBoxes.hh>
#include <Viewer/Selector.hh>
#include <Viewer/EventData.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/Event.hh>
using namespace Viewer;

ColourMasterUI::ColourMasterUI( RectPtr rect )
  : fRect( rect ), fGUIManager( rect )
{

}

void 
ColourMasterUI::NewEvent( const Event& event )
{
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
ColourMasterUI::EventLoop()
{
  EventData& events = EventData::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
	{
	case 0: // GUI Colour Selector
	  GUIColourPalette::gPalette = fGUIColourFactory.New( fGUIColourSelector->GetStringState() );
	  // Notify the GUI textures that they have changed...
	  GUITextureManager::GetInstance().ChangeColourScheme();
	  break;
	case 1: // Event Colour Selector
	  ColourPalette::gPalette = fColourFactory.New( fColourSelector->GetStringState() );
	  break;
	}
      fEvents.pop();
    }
}

void 
ColourMasterUI::SaveConfiguration( ConfigurationTable& configTable )
{
  // Just save current desktop
}

void 
ColourMasterUI::Initialise()
{
  sf::Rect<double> size;
  size.Left = 0.8; size.Top = 0.1; size.Width = 0.1; size.Height = 0.05;
  size.Top = 0.0; size.Left = 0.0; size.Height = 0.45; size.Width = 1.0;
  fGUIColourSelector = fGUIManager.NewGUI<GUIs::Selector>( size );
  fGUIColourSelector->Initialise( fGUIColourFactory.GetNames() );

  size.Top = 0.55; size.Left = 0.0; size.Height = 0.45; size.Width = 1.0;
  fColourSelector = fGUIManager.NewGUI<GUIs::Selector>( size );
  fColourSelector->Initialise( fColourFactory.GetNames() );
}

void 
ColourMasterUI::LoadConfiguration( ConfigurationTable& configTable )
{
  // load current desktop
}

void 
ColourMasterUI::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}
