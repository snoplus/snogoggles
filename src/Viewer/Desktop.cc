#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/EventMasterUI.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

Desktop::Desktop( RectPtr desktopRect )
  : fRect( desktopRect )
{

}

Desktop::~Desktop()
{
  delete fEMUI;
  delete fFrameManager;
}

void 
Desktop::NewEvent( Event& event )
{
  // Check the UI first
  fEMUI->NewEvent( event );
  fFrameManager->NewEvent( event );
}
void 
Desktop::EventLoop()
{
  fEMUI->EventLoop();
  fFrameManager->EventLoop();
}

void 
Desktop::PreInitialise( const ConfigurationTable* configTable )
{
  // First initialise the UI
  sf::Rect<double> defaultSize;
  defaultSize.Left = 1.0 - 0.1; defaultSize.Top = 0.0; defaultSize.Width = 0.1; defaultSize.Height = 1.0 - 2.0 * 0.1;
  fEMUI = new EventMasterUI( RectPtr( fRect->NewDaughter( defaultSize, Rect::eLocal ) ) );
  // Now initialise the FrameManager
  defaultSize.Left = 0.0; defaultSize.Top = 0.0; defaultSize.Width = 1.0 - 0.1; defaultSize.Height = 1.0;
  RectPtr frameRect( fRect->NewDaughter( defaultSize, Rect::eLocal ) );
  fFrameManager = new FrameManager( frameRect, 0.1, 0.1 );
  if( configTable != NULL )
    {
      fEMUI->PreInitialise( configTable->GetTable( "eventMaster" ) );
      fFrameManager->PreInitialise( configTable->GetTable( "frameManager" ) );
    }
  else
    {
      fEMUI->PreInitialise( NULL );
      fFrameManager->PreInitialise( NULL );
    }
}

void 
Desktop::PostInitialise( const ConfigurationTable* configTable )
{
  if( configTable != NULL )
    {
      fEMUI->PostInitialise( configTable->GetTable( "eventMaster" ) );
      fFrameManager->PostInitialise( configTable->GetTable( "frameManager" ) );
    }
  else
    {
      fEMUI->PostInitialise( NULL );
      fFrameManager->PostInitialise( NULL );
    }
}

void 
Desktop::SaveConfiguration( ConfigurationTable* configTable )
{
  ConfigurationTable* emTable = configTable->NewTable( "eventMaster" );
  fEMUI->SaveConfiguration( emTable );
  ConfigurationTable* fmTable = configTable->NewTable( "frameManager" );
  fFrameManager->SaveConfiguration( fmTable );
}

void 
Desktop::Render2d( RWWrapper& renderApp )
{
  RenderState renderState = fEMUI->GetRenderState();
  fFrameManager->Render2d( renderApp, renderState );
}

void 
Desktop::Render3d( RWWrapper& renderApp )
{
  RenderState renderState = fEMUI->GetRenderState();
  fFrameManager->Render3d( renderApp, renderState );
}

void 
Desktop::RenderGUI( RWWrapper& renderApp )
{
  RenderState renderState = fEMUI->GetRenderState();
  fFrameManager->RenderGUI( renderApp, renderState );
  fEMUI->Render( renderApp );
}
