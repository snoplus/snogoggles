#include <SFML/Graphics/Rect.hpp>

#include <vector>
using namespace std;

#include <Viewer/Desktop.hh>
#include <Viewer/Rect.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/EventMasterUI.hh>
#include <Viewer/RenderState.hh>
using namespace Viewer;

Desktop::Desktop( RectPtr desktopRect,
		  double rightMargin,
		  double bottomMargin )
  : fRect( desktopRect ), fBottomMargin( bottomMargin ), fRightMargin( rightMargin )
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
Desktop::SaveConfiguration( ConfigurationTable& configTable )
{
  //for( vector<Desktop*>::iterator iTer = fDesktops.begin(); iTer != fDesktops.end(); iTer++ )
    // Need names of tables
}

void 
Desktop::Initialise()
{
  // First initialise the UI
  sf::Rect<double> defaultSize;
  defaultSize.Left = 1.0 - fRightMargin; defaultSize.Top = 0.0; defaultSize.Width = fRightMargin; defaultSize.Height = 1.0 - 2.0 * fBottomMargin;
  fEMUI = new EventMasterUI( RectPtr( fRect->NewDaughter( defaultSize, Rect::eLocal ) ) );
  fEMUI->Initialise();
  // Now initialise the FrameManager
  defaultSize.Left = 0.0; defaultSize.Top = 0.0; defaultSize.Width = 1.0 - fRightMargin; defaultSize.Height = 1.0;
  RectPtr frameRect( fRect->NewDaughter( defaultSize, Rect::eLocal ) );
  fFrameManager = new FrameManager( frameRect, fRightMargin, fBottomMargin );
  fFrameManager->Initialise();
}

void 
Desktop::LoadConfiguration( ConfigurationTable& configTable )
{
  Initialise();
  //for( vector<Desktop*>::iterator iTer = fDesktops.begin(); iTer != fDesktops.end(); iTer++ )
    // Need names of tables
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
