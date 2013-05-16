#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/EventPanel.hh>
#include <Viewer/FramePanel.hh>
#include <Viewer/ScalingPanel.hh>
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
  delete fScalingPanel;
  delete fFrameManager;
}

void 
Desktop::NewEvent( Event& event )
{
  // Check the UI first
  fEventPanel->NewEvent( event );
  fFramePanel->NewEvent( event );
  fFrameManager->NewEvent( event );
  fScalingPanel->NewEvent( event );
}
void 
Desktop::EventLoop()
{
  fFrameManager->Reset();
  fEventPanel->EventLoop();
  fFramePanel->EventLoop();
  fFrameManager->EventLoop();
  fScalingPanel->EventLoop();
}

void 
Desktop::PreInitialise( const ConfigurationTable* configTable )
{
  // First initialise the UI
  fEventPanel = new EventPanel( RectPtr( fRect->NewDaughter() ), fRenderState );
  // Now initialise the FrameManager
  RectPtr frameMotherRect = RectPtr( fRect->NewDaughter() );
  fFrameManager = new FrameManager( frameMotherRect );
  // Now the FramePanel
  fFramePanel = new FramePanel( RectPtr( fRect->NewDaughter() ), frameMotherRect, *fFrameManager );
  // Now the ScalingPanel
  fScalingPanel = new ScalingPanel( RectPtr( fRect->NewDaughter() ), fRenderState );
  if( configTable != NULL )
    {
      fEventPanel->PreInitialise( configTable->GetTable( "eventPanel" ) );
      fFramePanel->PreInitialise( configTable->GetTable( "framePanel" ) );
      fFrameManager->PreInitialise( configTable->GetTable( "frameManager" ) );
      fScalingPanel->PreInitialise( configTable->GetTable( "scalingPanel" ) );
    }
  else
    {
      fEventPanel->PreInitialise( NULL );
      fFramePanel->PreInitialise( NULL );
      fFrameManager->PreInitialise( NULL );
      fScalingPanel->PreInitialise( NULL );
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
      fScalingPanel->PostInitialise( configTable->GetTable( "scalingPanel" ) );
    }
  else
    {
      fEventPanel->PostInitialise( NULL );
      fFramePanel->PostInitialise( NULL );
      fFrameManager->PostInitialise( NULL );
      fScalingPanel->PostInitialise( NULL );
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
  ConfigurationTable* spTable = configTable->NewTable( "scalingPanel" );
  fScalingPanel->SaveConfiguration( fmTable );
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
  fFrameManager->Render2d( renderApp, fRenderState );
  if( fScreenshotMode )
    {
      sf::Rect<double> size;
      size.left= 0.0; size.top= 0.96; size.width = 1.0; size.height = 0.02;
      EventSummary evSum( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
      evSum.Render( renderApp, fRenderState );
    }
}

void 
Desktop::Render3d( RWWrapper& renderApp )
{
  fFrameManager->Render3d( renderApp, fRenderState );
}

void 
Desktop::RenderGUI( RWWrapper& renderApp )
{
  fFrameManager->RenderGUI( renderApp, fRenderState );
  fEventPanel->Render( renderApp );
  fFramePanel->Render( renderApp );
  fScalingPanel->Render( renderApp );
}

void
Desktop::ToggleScreenshot( bool enable )
{
  fScreenshotMode = enable;
  fFrameManager->ToggleScreenshot( fScreenshotMode );
  fFramePanel->SetEnable( !fScreenshotMode );
  fEventPanel->SetEnable( !fScreenshotMode );
}
