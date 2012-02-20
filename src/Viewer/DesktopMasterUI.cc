#include <Viewer/DesktopMasterUI.hh>
using namespace Viewer;

DesktopMasterUI::DesktopMasterUI( RectPtr rect,
				  unsigned int numDesktops )
  : fRect( rect ), fNumDesktops( numDesktops )
{

}

void 
DesktopMasterUI::NewEvent( const Event& event )
{

}

void 
DesktopMasterUI::EventLoop()
{

}

void 
DesktopMasterUI::SaveConfiguration( ConfigurationTable& configTable )
{
  // Just save current desktop
}

void 
DesktopMasterUI::Initialise()
{

}

void 
DesktopMasterUI::LoadConfiguration( ConfigurationTable& configTable )
{
  // load current desktop
}

void 
DesktopMasterUI::RenderGUI( RWWrapper& renderApp )
{

}
