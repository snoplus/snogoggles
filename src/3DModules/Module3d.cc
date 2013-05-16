#include <Viewer/Module3d.hh>
using namespace Viewer;

Module3d::Module3d( RectPtr rect )
  : fRect( rect ), fGUIManager( rect )
{

}

Module3d::~Module3d()
{

}

void 
Module3d::NewEvent( const Event& event )
{
  vector<GUIEvent> guiEvents = fGUIManager.NewEvent( event );
  for( vector<GUIEvent>::const_iterator iTer = guiEvents.begin(); iTer != guiEvents.end(); iTer++ )
    if( iTer->IsNULL() == false )
      fEvents.push( *iTer );
}

void
Module3d::RenderGUI( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}
