#include <SFML/Window/Event.hpp>

using namespace std;

#include <Viewer/ScriptPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Selector.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Directory.hh>
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
  DataStore& events = DataStore::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Change the sum script

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
      dynamic_cast<GUIs::Selector*>( fGUIs[0] )->SetState( configTable->GetI( "sum-script_state" ) );
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
          sf::Rect<double> posRect( objectConfig->GetD( "x" ), objectConfig->GetD( "y" ), objectConfig->GetD( "width" ), objectConfig->GetD( "height" ) );
          switch( objectConfig->GetI( "effect" ) )
            {
            case 0:
              {
                fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, objectConfig->GetI( "effect" ) );
                stringstream scriptDir;
                scriptDir << getenv( "VIEWERROOT" ) << "/scripts/sum";
                dynamic_cast<GUIs::Selector*>( fGUIs[0] )->Initialise( GetFilesInDirectory( scriptDir.str(), string("py") ) );
              }
              break;
            case 1:
              {
                fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::Selector >( posRect, objectConfig->GetI( "effect" ) );
                stringstream scriptDir;
                scriptDir << getenv( "VIEWERROOT" ) << "/scripts/select";
                dynamic_cast<GUIs::Selector*>( fGUIs[1] )->Initialise( GetFilesInDirectory( scriptDir.str() ) );
              }
              break;
            }
        }
    }
}

void
ScriptPanel::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "sum-script_state", dynamic_cast<GUIs::Selector*>( fGUIs[0] )->GetState() );
}
