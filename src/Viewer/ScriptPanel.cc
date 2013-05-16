#include <SFML/Window/Event.hpp>

using namespace std;

#include <Viewer/ScriptPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/Selector.hh>
#include <Viewer/TextBox.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Directory.hh>
#include <Viewer/Button.hh>
#include <Viewer/PersistLabel.hh>
using namespace Viewer;

ScriptPanel::ScriptPanel( RectPtr rect )
  : Panel( rect, "ScriptPanel" )
{

}

ScriptPanel::~ScriptPanel()
{

}

void
ScriptPanel::EventLoop()
{
  DataSelector& dataSelector = DataSelector::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case eAnalSelect: // Change the analysis script
        case eAnalRefresh:
          dataSelector.SetAnalysisScript( dynamic_cast<GUIs::Selector*>( fGUIs[eAnalSelect] )->GetStringState() );
          break;
        case eAnalOn:
          dataSelector.SetAnalyse( dynamic_cast<GUIs::PersistLabel*>( fGUIs[eAnalOn] )->GetState() );
          break;
        case eEventSelect: // Change the analysis script
        case eEventRefresh:
          dataSelector.SetEventSelectionScript( dynamic_cast<GUIs::Selector*>( fGUIs[eEventSelect] )->GetStringState() );
          break;
        case eEventOn:
          dataSelector.SetSelect( dynamic_cast<GUIs::PersistLabel*>( fGUIs[eEventOn] )->GetState() );
          break;
        case eEventInput:
          dataSelector.SetEventSelectionInput( dynamic_cast<GUIs::TextBox*>( fGUIs[eEventInput] )->GetString() );
          break;
        }
      fEvents.pop();
    }
}

void 
ScriptPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
  if( configTable != NULL )
    {
      dynamic_cast<GUIs::Selector*>( fGUIs[eAnalSelect] )->SetState( configTable->GetI( "sum-script_state" ) );
    }
}

void
ScriptPanel::PostInitialise( const ConfigurationTable* configTable )
{

}

void
ScriptPanel::LoadGUIConfiguration( const ConfigurationTable* config )
{
  for( unsigned int uGUIs = 0; uGUIs < config->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = config->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) )
        {
          sf::Rect<double> posRect = LoadRect( objectConfig, fRect );
          const int effect = objectConfig->GetI( "effect" );
          switch( effect )
            {
            case eAnalSelect:
              {
                fGUIs[effect]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, effect );
                stringstream scriptDir;
                scriptDir << getenv( "VIEWERROOT" ) << "/scripts/analysis";
                dynamic_cast<GUIs::Selector*>( fGUIs[effect] )->Initialise( GetFilesInDirectory( scriptDir.str(), string("py"), string("anal_") ) );
              }
              break;
            case eEventSelect:
              {
                fGUIs[effect]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, effect );
                stringstream scriptDir;
                scriptDir << getenv( "VIEWERROOT" ) << "/scripts/eventselect";
                dynamic_cast<GUIs::Selector*>( fGUIs[effect] )->Initialise( GetFilesInDirectory( scriptDir.str(), string("py"), string("evselect_") ) );
              }
              break;
            case ePMTSelect:
              {
                fGUIs[effect]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, effect );
                stringstream scriptDir;
                scriptDir << getenv( "VIEWERROOT" ) << "/scripts/pmtselect";
                dynamic_cast<GUIs::Selector*>( fGUIs[effect] )->Initialise( GetFilesInDirectory( scriptDir.str() ) );
              }
              break;
            case eAnalRefresh: 
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
                dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 44 );
              }
              break;
            case eEventRefresh: 
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
                dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 44 );
              }
              break;
            case ePMTRefresh: 
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
                dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 44 );
              }
              break;
            case eAnalOn: 
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::PersistLabel >( posRect, effect );
                dynamic_cast<GUIs::PersistLabel*>( fGUIs[effect] )->Initialise( 16, "Enable" );
              }
              break;
            case eEventOn: 
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::PersistLabel >( posRect, effect );
                dynamic_cast<GUIs::PersistLabel*>( fGUIs[effect] )->Initialise( 16, "Enable" );
              }
              break;
            case ePMTOn: 
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::PersistLabel >( posRect, effect );
                dynamic_cast<GUIs::PersistLabel*>( fGUIs[effect] )->Initialise( 16, "Enable" );
              }
              break;
            case eEventInput:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::TextBox >( posRect, effect );
              }
              break;
            }
        }
    }
}

void
ScriptPanel::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "sum-script_state", dynamic_cast<GUIs::Selector*>( fGUIs[eAnalSelect] )->GetState() );
}
