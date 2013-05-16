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
  vector<GUIEvent> guiEvents = fGUIManager.NewEvent( event );
  for( vector<GUIEvent>::const_iterator iTer = guiEvents.begin(); iTer != guiEvents.end(); iTer++ )
    if( iTer->IsNULL() == false )
      fEvents.push( *iTer );
}

void
Frame2d::RenderGUI( RWWrapper& renderApp,
                    const RenderState& renderState )
{
  fGUIManager.Render( renderApp );
}
