#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/EventPanel.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

Desktop::Desktop( RectPtr desktopRect )
  : fRect( desktopRect )
{

}

Desktop::~Desktop()
{
  delete fEventPanel;
  delete fFrameManager;
}

void 
Desktop::NewEvent( Event& event )
{
  // Check the UI first
  fEventPanel->NewEvent( event );
  fFrameManager->NewEvent( event );
}
void 
Desktop::EventLoop()
{
  fEventPanel->EventLoop();
  fFrameManager->EventLoop();
}

void 
Desktop::PreInitialise( const ConfigurationTable* configTable )
{
  // First initialise the UI
  sf::Rect<double> defaultSize;
  fEventPanel = new EventPanel( RectPtr( fRect->NewDaughter() ) );
  // Now initialise the FrameManager
  defaultSize.Left = 0.0; defaultSize.Top = 0.0; defaultSize.Width = 1.0 - 0.1; defaultSize.Height = 1.0;
  RectPtr frameRect( fRect->NewDaughter( defaultSize, Rect::eLocal ) );
  fFrameManager = new FrameManager( frameRect, 0.1, 0.1 );
  if( configTable != NULL )
    {
      fEventPanel->PreInitialise( configTable->GetTable( "eventPanel" ) );
      fFrameManager->PreInitialise( configTable->GetTable( "frameManager" ) );
    }
  else
    {
      fEventPanel->PreInitialise( NULL );
      fFrameManager->PreInitialise( NULL );
    }
}

void 
Desktop::PostInitialise( const ConfigurationTable* configTable )
{
  if( configTable != NULL )
    {
      fEventPanel->PostInitialise( configTable->GetTable( "eventPanel" ) );
      fFrameManager->PostInitialise( configTable->GetTable( "frameManager" ) );
    }
  else
    {
      fEventPanel->PostInitialise( NULL );
      fFrameManager->PostInitialise( NULL );
    }
}

void 
Desktop::SaveConfiguration( ConfigurationTable* configTable )
{
  ConfigurationTable* emTable = configTable->NewTable( "eventPanel" );
  fEventPanel->SaveConfiguration( emTable );
  ConfigurationTable* fmTable = configTable->NewTable( "frameManager" );
  fFrameManager->SaveConfiguration( fmTable );
}

void 
Desktop::Render2d( RWWrapper& renderApp )
{
  const RenderState renderState = fEventPanel->GetRenderState();
  fFrameManager->Render2d( renderApp, renderState );
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
}
