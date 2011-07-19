#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/EventUI.hh>
#include <Viewer/IncreaseButton.hh>
#include <Viewer/DecreaseButton.hh>
#include <Viewer/EventData.hh>
using namespace Viewer;
using namespace Frames;

void 
EventUI::Initialise()
{
  sf::Rect<double> forward( 0.7, 0.7, 0.2, 0.2 );
  fNextButton = fGUIManager.NewGUI<GUIs::IncreaseButton>( forward );
  sf::Rect<double> back( 0.1, 0.7, 0.2, 0.2 );
  fPrevButton = fGUIManager.NewGUI<GUIs::DecreaseButton>( back );

  fEVInfoText = Text( "" );
  fEVInfoText.SetColor( sf::Color( 0, 0, 0 ) );
  fEVInfoText.SetBoundingRect( sf::Rect<double>( 0.1, 0.1, 0.8, 0.25 ) );  
  fEVID = 0;
  fEVCount = 1;
  fMCInfoText = Text( "" );
  fMCInfoText.SetColor( sf::Color( 0, 0, 0 ) );
  fMCInfoText.SetBoundingRect( sf::Rect<double>( 0.1, 0.4, 0.8, 0.25 ) );
  fMCID = -1;
}

void 
EventUI::EventLoop()
{
  EventData& events = EventData::GetInstance();
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID == 0 && !fNextButton->GetState() )
	{
	  events.NextEV();
	  events.GetEVData( fEVID, fEVCount );
	  events.GetMCData( fMCID, fMCCount );
	}
      else if( fEvents.front().fguiID == 1 && !fPrevButton->GetState() )
	{
	  events.PreviousEV();
	  events.GetEVData( fEVID, fEVCount );
	  events.GetMCData( fMCID, fMCCount );
	}
      fEvents.pop();
    }
}
void 
EventUI::Render2d( RWWrapper& windowApp )
{
  stringstream eventInfo;
  eventInfo << "EV: " << fEVID << "\n" << fEVCount << " loaded.";
  fEVInfoText.SetString( eventInfo.str().c_str() );
  windowApp.Draw( fEVInfoText );  
  eventInfo.str("");

  if( fMCID != -1 )
    {
      eventInfo << "MC: " << fMCID << "\n" << fMCCount << " loaded.";
      fMCInfoText.SetString( eventInfo.str().c_str() );
      windowApp.Draw( fMCInfoText );
    }
}
