#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
using namespace std;

#include <Viewer/MasterUI.hh>
#include <Viewer/ExitButton.hh>
#include <Viewer/FrameFactory.hh>
#include <Viewer/FrameManager.hh>
using namespace Viewer;
using namespace Frames;

MasterUI::MasterUI( FrameManager* manager )
  : fFrameManager( manager )
{
  FrameFactory a;
  fFrameNames = a.GetNames();
  for( unsigned int uLoop = 0; uLoop < fFrameNames.size(); uLoop++ )
    {
      double width = 1.0 / (double)fFrameNames.size();
      sf::Rect<double> forward( width * (double)uLoop, 0.1, width, 0.8 );
      fButtons.push_back( fGUIManager.NewGUI<GUIs::ExitButton>( forward ) );
    }
}

void 
MasterUI::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( !fButtons[fEvents.front().fguiID]->GetState() )
	fFrameManager->NewFrame( fFrameNames[fEvents.front().fguiID] );
      fEvents.pop();
    }
}
