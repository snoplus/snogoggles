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
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void
Module3d::RenderGUI( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}
