#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/DesktopManager.hh>
#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/DesktopMasterUI.hh>
#include <Viewer/ColourMasterUI.hh>
using namespace Viewer;

DesktopManager::DesktopManager( RectPtr globalMother,
                                double rightMargin,
                                double bottomMargin )
  : fGlobalMother( globalMother ), fBottomMargin( bottomMargin ), fRightMargin( rightMargin )
{
  fDesktops.resize( 8 ); // Maximum allowed desktops
}

DesktopManager::~DesktopManager()
{
  for( unsigned int iDesktop = 0; iDesktop < fDesktops.size(); iDesktop++ )
    delete fDesktops[iDesktop];
  fDesktops.clear();
  delete fDMUI;
  delete fCMUI;
}

void 
DesktopManager::NewEvent( Event& event )
{
  // Check the UI first
  fDMUI->NewEvent( event ); 
  fCMUI->NewEvent( event );
  fDesktops[fDMUI->GetCurrentDesktop()]->NewEvent( event );
}
void 
DesktopManager::EventLoop()
{
  fDMUI->EventLoop();
  fCMUI->EventLoop();
  fDesktops[fDMUI->GetCurrentDesktop()]->EventLoop();
}

void 
DesktopManager::Initialise()
{
  // First initialise the UI
  sf::Rect<double> defaultSize; // The default size
  RectPtr dmRect( fGlobalMother->NewDaughter() );
  defaultSize.Left = 1.0 - fRightMargin; defaultSize.Top = 1.0 - fBottomMargin; defaultSize.Width = fRightMargin; defaultSize.Height = fBottomMargin;
  dmRect->SetRect( defaultSize, Rect::eLocal );
  fDMUI = new DesktopMasterUI( dmRect, fDesktops.size() );
  fDMUI->Initialise();
  defaultSize.Top = 1.0 - 2.0 * fBottomMargin; defaultSize.Height = fBottomMargin;
  fCMUI = new ColourMasterUI( RectPtr( fGlobalMother->NewDaughter( defaultSize, Rect::eLocal ) ) );
  fCMUI->Initialise();

  // Now initialise the Desktops
  for( int iDesktop = 0; iDesktop < fDesktops.size(); iDesktop++ )
    {
      RectPtr desktopRect( fGlobalMother->NewDaughter() );
      sf::Rect<double> defaultSize; // The default desktop size
      defaultSize.Left = 0.0; defaultSize.Top = 0.0; defaultSize.Width = 1.0; defaultSize.Height = 1.0;
      desktopRect->SetRect( defaultSize, Rect::eLocal );
      fDesktops[iDesktop] = new Desktop( desktopRect, fRightMargin, fBottomMargin );
      fDesktops[iDesktop]->Initialise();
    }
}

void 
DesktopManager::LoadConfiguration( const ConfigurationTable* config )
{
  unsigned int uDesktop = 0;
  for( vector< ConfigurationTable* >::const_iterator iTer = config->GetTableBegin(); iTer != config->GetTableEnd(); iTer++ )
    {
      const ConfigurationTable* configTable = *iTer;
      fDesktops[uDesktop]->LoadConfiguration( configTable );
      uDesktop++;
    }
  fDMUI->LoadConfiguration( config );
}

void 
DesktopManager::SaveConfiguration( ConfigurationTable* config )
{
  unsigned int uDesktop = 0;
  for( vector<Desktop*>::iterator iTer = fDesktops.begin(); iTer != fDesktops.end(); iTer++ )
    {
      ConfigurationTable* configTable = config->NewTable( "Desktop" );
      fDesktops[uDesktop]->SaveConfiguration( configTable );
      uDesktop++;
    }
  fDMUI->SaveConfiguration( config );
}

void 
DesktopManager::Render2d( RWWrapper& renderApp )
{
  fDesktops[fDMUI->GetCurrentDesktop()]->Render2d( renderApp );
}

void 
DesktopManager::Render3d( RWWrapper& renderApp )
{
  fDesktops[fDMUI->GetCurrentDesktop()]->Render3d( renderApp );
}

void 
DesktopManager::RenderGUI( RWWrapper& renderApp )
{
  fDMUI->Render( renderApp );
  fCMUI->Render( renderApp );
  fDesktops[fDMUI->GetCurrentDesktop()]->RenderGUI( renderApp );
}
