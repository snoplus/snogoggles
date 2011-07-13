#include <SFML/Window/Event.hpp>

#include <Viewer/Frame.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;

void 
Frame::RenderGUI( sf::RenderWindow& windowApp )
{
  RWWrapper rWindowApp( windowApp, fFrameRect );
  fGUIManager.Render( rWindowApp );
}

void 
Frame::NewEvent( UIEvent& event )
{
  // New Mother rect, thus new UIEvent
  UIEvent uiEvent( event, fFrameRect ); 
  GUIReturn retEvent = fGUIManager.NewEvent( uiEvent );
  if( retEvent.IsNULL() == false )
    fEvents.push( retEvent );
}
   
void 
Frame::Initialise( ConfigurationTable& configTable )
{

}

void 
Frame::SaveConfiguration( ConfigurationTable& configTable )
{

}
