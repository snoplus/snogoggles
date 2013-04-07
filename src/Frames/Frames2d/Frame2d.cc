#include <Viewer/Frame2d.hh>
using namespace Viewer;

Frame2d::Frame2d( RectPtr rect )
  : Frame( rect ), fGUIManager( rect )
{

}

Frame2d::~Frame2d()
{

}

void 
Frame2d::NewEvent( const Event& event )
{
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void
Frame2d::RenderGUI( RWWrapper& renderApp,
                    const RenderState& renderState )
{
  fGUIManager.Render( renderApp );
}
