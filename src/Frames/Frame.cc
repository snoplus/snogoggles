#include <Viewer/Frame.hh>
using namespace Viewer;

Frame::Frame( RectPtr rect )
  : fRect( rect ), fGUIManager( rect )
{

}

Frame::~Frame()
{

}

void 
Frame::NewEvent( const Event& event )
{
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
Frame::SaveConfiguration( ConfigurationTable* configTable )
{

}

void 
Frame::Initialise()
{
  
}

void 
Frame::LoadConfiguration( const ConfigurationTable* configTable )
{

}

void
Frame::RenderGUI( RWWrapper& renderApp,
		  const RenderState& renderState )
{
  fGUIManager.Render( renderApp );
}
