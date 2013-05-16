#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/EventPanel.hh>
#include <Viewer/FramePanel.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/EventSummary.hh>
using namespace Viewer;

Desktop::Desktop( RectPtr desktopRect )
  : fRect( desktopRect ), fScreenshotMode( false )
{

}

Desktop::~Desktop()
{
  delete fEventPanel;
  delete fFramePanel;
  delete fFrameManager;
}

void 
Desktop::NewEvent( Event& event )
{
  // Check the UI first
  fEventPanel->NewEvent( event );
  fFramePanel->NewEvent( event );
  fFrameManager->NewEvent( event );
}
void 
Desktop::EventLoop()
{
  fFrameManager->Reset();
  fEventPanel->EventLoop();
  fFramePanel->EventLoop();
  fFrameManager->EventLoop();
}

void 
Desktop::PreInitialise( const ConfigurationTable* configTable )
{
  // First initialise the UI
  fEventPanel = new EventPanel( RectPtr( fRect->NewDaughter() ) );
  // Now initialise the FrameManager
  RectPtr frameMotherRect = RectPtr( fRect->NewDaughter() );
  fFrameManager = new FrameManager( frameMotherRect );
  // Now the FramePanel
  fFramePanel = new FramePanel( RectPtr( fRect->NewDaughter() ), frameMotherRect, *fFrameManager );
  if( configTable != NULL )
    {
      fEventPanel->PreInitialise( configTable->GetTable( "eventPanel" ) );
      fFramePanel->PreInitialise( configTable->GetTable( "framePanel" ) );
      fFrameManager->PreInitialise( configTable->GetTable( "frameManager" ) );
    }
  else
    {
      fEventPanel->PreInitialise( NULL );
      fFramePanel->PreInitialise( NULL );
      fFrameManager->PreInitialise( NULL );
    }
}

void 
Desktop::PostInitialise( const ConfigurationTable* configTable )
{
  if( configTable != NULL )
    {
      fEventPanel->PostInitialise( configTable->GetTable( "eventPanel" ) );
      fFramePanel->PostInitialise( configTable->GetTable( "framePanel" ) );
      fFrameManager->PostInitialise( configTable->GetTable( "frameManager" ) );
    }
  else
    {
      fEventPanel->PostInitialise( NULL );
      fFramePanel->PostInitialise( NULL );
      fFrameManager->PostInitialise( NULL );
    }
}

void 
Desktop::SaveConfiguration( ConfigurationTable* configTable )
{
  ConfigurationTable* epTable = configTable->NewTable( "eventPanel" );
  fEventPanel->SaveConfiguration( epTable );
  ConfigurationTable* fpTable = configTable->NewTable( "framePanel" );
  fFramePanel->SaveConfiguration( fpTable );
  ConfigurationTable* fmTable = configTable->NewTable( "frameManager" );
  fFrameManager->SaveConfiguration( fmTable );
}

void
Desktop::ProcessData( bool force )
{
  // Process run first, suppliers the channel information
  if( force || DataSelector::GetInstance().RunChanged() )
    {
      fFrameManager->ProcessRun();
    }
  if( force || fEventPanel->GetRenderState().HasChanged() || GUIProperties::GetInstance().HasChanged() || 
      DataSelector::GetInstance().EventChanged() || fFrameManager->HasChanged() ) 
    {
      fFrameManager->ProcessEvent( fEventPanel->GetRenderState() );
    }
}

void 
Desktop::Render2d( RWWrapper& renderApp )
{
  const RenderState renderState = fEventPanel->GetRenderState();
  fFrameManager->Render2d( renderApp, renderState );
  if( fScreenshotMode )
    {
      sf::Rect<double> size;
      size.left= 0.0; size.top= 0.96; size.width = 1.0; size.height = 0.02;
      EventSummary evSum( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
      evSum.Render( renderApp, renderState );
    }
}

void 
Desktop::Render3d( RWWrapper& renderApp )
{
  const RenderState renderState = fEventPanel->GetRenderState();
  fFrameManager->Render3d( renderApp, renderState );
}

void 
Desktop::RenderGUI( RWWrapper& renderApp )
{
  const RenderState renderState = fEventPanel->GetRenderState();
  fFrameManager->RenderGUI( renderApp, renderState );
  fEventPanel->Render( renderApp );
  fFramePanel->Render( renderApp );
}

void
Desktop::ToggleScreenshot( bool enable )
{
  fScreenshotMode = enable;
  fFrameManager->ToggleScreenshot( fScreenshotMode );
  fFramePanel->SetEnable( !fScreenshotMode );
  fEventPanel->SetEnable( !fScreenshotMode );
}
