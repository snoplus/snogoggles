#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/DesktopManager.hh>
#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/DesktopPanel.hh>
#include <Viewer/GUIPanel.hh>
#include <Viewer/ScriptPanel.hh>
using namespace Viewer;

DesktopManager::DesktopManager( RectPtr globalMother )
  : fGlobalMother( globalMother )
{
  fDesktops.resize( 8 ); // Maximum allowed desktops
}

DesktopManager::~DesktopManager()
{
  for( unsigned int iDesktop = 0; iDesktop < fDesktops.size(); iDesktop++ )
    delete fDesktops[iDesktop];
  fDesktops.clear();
  delete fDesktopPanel;
  delete fGUIPanel;
  delete fScriptPanel;
}

void 
DesktopManager::NewEvent( Event& event )
{
  // Check the UI first
  fDesktopPanel->NewEvent( event ); 
  fGUIPanel->NewEvent( event );
  fScriptPanel->NewEvent( event );
  fDesktops[fDesktopPanel->GetCurrentDesktop()]->NewEvent( event );
}
void 
DesktopManager::EventLoop()
{
  fDesktopPanel->EventLoop();
  fGUIPanel->EventLoop();
  fScriptPanel->EventLoop();
  fDesktops[fDesktopPanel->GetCurrentDesktop()]->EventLoop();
}

void 
DesktopManager::PreInitialise( const ConfigurationTable* configTable )
{
  fDesktopPanel = new DesktopPanel( RectPtr( fGlobalMother->NewDaughter() ) );
  fDesktopPanel->PreInitialise( configTable );
  fGUIPanel = new GUIPanel( RectPtr( fGlobalMother->NewDaughter() ) );
  fGUIPanel->PreInitialise( configTable );
  fScriptPanel = new ScriptPanel( RectPtr( fGlobalMother->NewDaughter() ) );
  fScriptPanel->PreInitialise( configTable );

  // Now initialise the Desktops
  for( int iDesktop = 0; iDesktop < fDesktops.size(); iDesktop++ )
    {
      sf::Rect<double> defaultSize( 0.0, 0.0, 1.0, 1.0 );
      fDesktops[iDesktop] = new Desktop( RectPtr( fGlobalMother->NewDaughter( defaultSize, Rect::eLocal ) ) );
      stringstream tableName;
      tableName << "Desktop" << iDesktop;
      if( configTable != NULL )
        fDesktops[iDesktop]->PreInitialise( configTable->GetTable( tableName.str() ) );
      else
        fDesktops[iDesktop]->PreInitialise( NULL );
    }
}

void 
DesktopManager::PostInitialise( const ConfigurationTable* configTable )
{
  fDesktopPanel->PostInitialise( configTable );
  fGUIPanel->PostInitialise( configTable );
  fScriptPanel->PostInitialise( configTable );
  for( int iDesktop = 0; iDesktop < fDesktops.size(); iDesktop++ )
    {
      stringstream tableName;
      tableName << "Desktop" << iDesktop;
      if( configTable != NULL )
        fDesktops[iDesktop]->PostInitialise( configTable->GetTable( tableName.str() ) );
      else
        fDesktops[iDesktop]->PostInitialise( NULL );
    }
}

void 
DesktopManager::SaveConfiguration( ConfigurationTable* configTable )
{
  for( int iDesktop = 0; iDesktop < fDesktops.size(); iDesktop++ )
    {
      stringstream tableName;
      tableName << "Desktop" << iDesktop;
      fDesktops[iDesktop]->SaveConfiguration( configTable->NewTable( tableName.str() ) );
    }
  fGUIPanel->SaveConfiguration( configTable );
  fScriptPanel->SaveConfiguration( configTable );
  fDesktopPanel->SaveConfiguration( configTable );
}

void 
DesktopManager::Render2d( RWWrapper& renderApp )
{
  fDesktops[fDesktopPanel->GetCurrentDesktop()]->Render2d( renderApp );
}

void 
DesktopManager::Render3d( RWWrapper& renderApp )
{
  fDesktops[fDesktopPanel->GetCurrentDesktop()]->Render3d( renderApp );
}

void 
DesktopManager::RenderGUI( RWWrapper& renderApp )
{
  fDesktopPanel->Render( renderApp );
  fGUIPanel->Render( renderApp );
  fScriptPanel->Render( renderApp );
  fDesktops[fDesktopPanel->GetCurrentDesktop()]->RenderGUI( renderApp );
}
