#include <Viewer/GUIManager.hh>
#include <Viewer/UIEvent.hh>
#include <Viewer/GUI.hh>
using namespace Viewer;

UIEvent 
GUIManager::NewEvent( sf::Event& event )
{
  // TODO 
}
  
void 
GUIManager::Render( sf::RenderWindow& windowApp )
{
  for( unsigned int uGUI = 0; uGUI < fGUIObjects.size(); uGUI++ )
    fGUIObjects[uGUI]->Render( windowApp );
}
  

template<class T>
GUI* 
GUIManager::NewGUI( sf::Rect<double>& rect )
{
  GUI* gui = new T( rect, fGUIObjects.size() );
  fGUIObjects.push_back( gui );
  return gui;
}

GUI* 
GUIManager::GetGUI( unsigned int guiID )
{
  return fGUIObjects[guiID];
}
