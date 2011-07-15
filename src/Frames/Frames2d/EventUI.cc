#include <SFML/Graphics.hpp>

#include <Viewer/EventUI.hh>
#include <Viewer/ExitButton.hh>
#include <Viewer/EventData.hh>
using namespace Viewer;
using namespace Frames;

void 
EventUI::Initialise()
{
  sf::Rect<double> forward( 0.7, 0.7, 0.2, 0.2 );
  fNextButton = fGUIManager.NewGUI<GUIs::ExitButton>( forward );
  sf::Rect<double> back( 0.1, 0.7, 0.2, 0.2 );
  fPrevButton = fGUIManager.NewGUI<GUIs::ExitButton>( back );
}

void 
EventUI::EventLoop()
{
  EventData& events = EventData::GetInstance();
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID == 0 && !fNextButton->GetState() )
	events.NextEV();
      else if( fEvents.front().fguiID == 1 && !fPrevButton->GetState() )
	events.PreviousEV();
      fEvents.pop();
    }
}
void 
EventUI::Render2d( RWWrapper& windowApp )
{
  
}
