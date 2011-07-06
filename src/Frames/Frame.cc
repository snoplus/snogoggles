#include <SFML/Window/Event.hpp>

#include <Viewer/Frame.hh>
#include <Viewer/UIEvent.hh>
using namespace Viewer;

void 
Frame::RenderGUI( sf::RenderWindow& windowApp )
{
  RWWrapper rWindowApp( windowApp, fFrameCoord );
  fGUIManager.Render( rWindowApp );
}

void 
Frame::NewEvent( sf::Event& event )
{
  UIEvent uiEvent( event, fFrameCoord );
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
