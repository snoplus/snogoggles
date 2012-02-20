#include <Viewer/EventMasterUI.hh>
using namespace Viewer;

EventMasterUI::EventMasterUI( RectPtr rect )
  : fRect( rect )
{

}

void 
EventMasterUI::NewEvent( const Event& event )
{

}

void 
EventMasterUI::EventLoop()
{

}

void 
EventMasterUI::SaveConfiguration( ConfigurationTable& configTable )
{
  // Just save current desktop
}

void 
EventMasterUI::Initialise()
{

}

void 
EventMasterUI::LoadConfiguration( ConfigurationTable& configTable )
{
  // load current desktop
}

void 
EventMasterUI::RenderGUI( RWWrapper& renderApp )
{

}

RenderState 
EventMasterUI::GetRenderState()
{
  return RenderState();
}
