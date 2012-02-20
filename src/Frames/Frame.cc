#include <Viewer/Frame.hh>
//#include <Viewer/GUIManager.hh>
using namespace Viewer;

Frame::Frame( RectPtr rect )
  : fRect( rect )
{

}

void 
Frame::NewEvent( const Event& event )
{
  //GUIEvent guiEvent = fGUIManager->NewEvent( event );
  //if( guiEvent.IsNULL() == false )
  //  fEvents.push( guiEvent );
}

void 
Frame::Initialise()
{
  //fGUIManager = new GUIManager( fRect ); //Use same Rect as Frame
}

void
Frame::RenderGUI( RWWrapper& renderApp,
		  const RenderState& renderState )
{

}
