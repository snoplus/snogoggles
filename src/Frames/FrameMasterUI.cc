#include <string>
using namespace std;

#include <Viewer/FrameMasterUI.hh>
using namespace Viewer;

FrameMasterUI::FrameMasterUI( RectPtr rect )
  : fRect( rect )
{

}

string 
FrameMasterUI::NewEvent( const Event& event )
{
  return string("");
}

void 
FrameMasterUI::EventLoop()
{

}

void 
FrameMasterUI::SaveConfiguration( ConfigurationTable& configTable )
{
  // Just save current desktop
}

void 
FrameMasterUI::Initialise()
{

}

void 
FrameMasterUI::LoadConfiguration( ConfigurationTable& configTable )
{
  // load current desktop
}

void 
FrameMasterUI::RenderGUI( RWWrapper& renderApp )
{

}
