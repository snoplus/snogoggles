#include <SFML/Window/Event.hpp>

#include <Viewer/GUIManager.hh>
#include <Viewer/UIEvent.hh>
#include <Viewer/GUI.hh>
using namespace Viewer;

UIEvent 
GUIManager::NewEvent( sf::Event& event )
{

}
  
void 
GUIManager::Render( sf::RenderWindow& windowApp, const FrameCoord& frameCoord )
{
  for( unsigned int uGUI = 0; uGUI < fGUIObjects.size(); uGUI++ )
    fGUIObjects[uGUI]->Render( windowApp, frameCoord );
}
  

GUI* 
GUIManager::GetGUI( unsigned int guiID )
{
  return fGUIObjects[guiID];
}
