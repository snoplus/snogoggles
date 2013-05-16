#include <SFML/Window/Event.hpp>

using namespace std;

#include <Viewer/GUIPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/Selector.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Directory.hh>
using namespace Viewer;

GUIPanel::GUIPanel( RectPtr rect )
  : Panel( rect, "GUIPanel" )
{

}

GUIPanel::~GUIPanel()
{

}

void
GUIPanel::EventLoop()
{
  GUIProperties::GetInstance().Reset();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Change in GUI colour
          GUIProperties::GetInstance().LoadGUIColourPalette( dynamic_cast<GUIs::Selector*>( fGUIs[0] )->GetStringState() );
          break;
        case 1: // Change in colour
          GUIProperties::GetInstance().LoadColourPalette( dynamic_cast<GUIs::Selector*>( fGUIs[1] )->GetStringState() );
          break;
        case 2: // Invert the gui
          GUIProperties::GetInstance().InvertGUI();
          break;
        }
      fEvents.pop();
    }
}

void 
GUIPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
  if( configTable != NULL )
    {
      dynamic_cast<GUIs::Selector*>( fGUIs[0] )->SetState( configTable->GetI( "gui-colour_state" ) );
      dynamic_cast<GUIs::Selector*>( fGUIs[1] )->SetState( configTable->GetI( "colour_state" ) );
      dynamic_cast<GUIs::PersistLabel*>( fGUIs[2] )->SetState( configTable->GetI( "inverted" ) );
      GUIProperties::GetInstance().LoadGUIColourPalette( dynamic_cast<GUIs::Selector*>( fGUIs[0] )->GetStringState() );
      GUIProperties::GetInstance().LoadColourPalette( dynamic_cast<GUIs::Selector*>( fGUIs[1] )->GetStringState() );
      if( configTable->GetI( "inverted" ) )
        GUIProperties::GetInstance().InvertGUI();
    }
}

void
GUIPanel::PostInitialise( const ConfigurationTable* configTable )
{

}

void
GUIPanel::LoadGUIConfiguration( const ConfigurationTable* config )
{
  for( unsigned int uGUIs = 0; uGUIs < config->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = config->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) )
        {
          sf::Rect<double> posRect = LoadRect( objectConfig, fRect );
          switch( objectConfig->GetI( "effect" ) )
            {
            case 0:
              {
                fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, objectConfig->GetI( "effect" ) );
                stringstream guiColourDir;
                guiColourDir << getenv( "VIEWERROOT" ) << "/gui/gui-colour";
                dynamic_cast<GUIs::Selector*>( fGUIs[0] )->Initialise( GetFilesInDirectory( guiColourDir.str(), string("xml") ) );
              }
              break;
            case 1:
              {
                fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, objectConfig->GetI( "effect" ) );
                stringstream guiColourDir;
                guiColourDir << getenv( "VIEWERROOT" ) << "/gui/colour";
                dynamic_cast<GUIs::Selector*>( fGUIs[1] )->Initialise( GetFilesInDirectory( guiColourDir.str(), string("xml") ) );
              }
              break;
            case 2:
              fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::PersistLabel >( posRect, objectConfig->GetI( "effect" ) );
              dynamic_cast< GUIs::PersistLabel* >( fGUIs[objectConfig->GetI( "effect" )] )->Initialise( 16, "Invert Colours?" );
              break;
            }
        }
    }
}

void
GUIPanel::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "gui-colour_state", dynamic_cast<GUIs::Selector*>( fGUIs[0] )->GetState() );
  configTable->SetI( "colour_state", dynamic_cast<GUIs::Selector*>( fGUIs[1] )->GetState() );
  configTable->SetI( "inverted", dynamic_cast<GUIs::PersistLabel*>( fGUIs[2] )->GetState() );
}
