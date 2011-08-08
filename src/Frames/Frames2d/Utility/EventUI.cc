#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/EventUI.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/EventData.hh>
using namespace Viewer;
using namespace Frames;

void 
EventUI::Initialise()
{
  fNextButton = fGUIManager.NewGUI<GUIs::GUIImageButton>( sf::Rect<double>( 0.8, 0.05, 0.1, 0.1 ) );
  fNextButton->Initialise( eIncrease );
  fPrevButton = fGUIManager.NewGUI<GUIs::GUIImageButton>( sf::Rect<double>( 0.1, 0.05, 0.1, 0.1 ) );
  fPrevButton->Initialise( eDecrease );
  fContinuous = fGUIManager.NewGUI<GUIs::CheckBoxLabel>( sf::Rect<double>( 0.25, 0.05, 0.5, 0.1 ) );
  fContinuous->SetLabel( "Continuous" );

  fEVInfoText = Text( "" );
  fEVInfoText.SetBoundingRect( sf::Rect<double>( 0.1, 0.2, 0.8, 0.2 ) );  
  fEVID = 0;
  fEVCount = 1;
  fMCInfoText = Text( "" );
  fMCInfoText.SetBoundingRect( sf::Rect<double>( 0.1, 0.4, 0.8, 0.2 ) );
  fMCID = -1;
  fClock.Reset();
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
  if( fContinuous->GetState() && fClock.GetElapsedTime() > 3000 )
    {
      events.NextEV();
      events.GetEVData( fEVID, fEVCount );
      events.GetMCData( fMCID, fMCCount );
      fClock.Reset();
    }    
}
void 
EventUI::Render2d( RWWrapper& windowApp )
{
  stringstream eventInfo;
  eventInfo << "EV: " << fEVID << "\n" << fEVCount << " loaded.";
  fEVInfoText.SetString( eventInfo.str().c_str() );
  fEVInfoText.SetColor( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  windowApp.Draw( fEVInfoText );  
  eventInfo.str("");

  if( fMCID != -1 )
    {
      eventInfo << "MC: " << fMCID << "\n" << fMCCount << " loaded.";
      fMCInfoText.SetString( eventInfo.str().c_str() );
      fMCInfoText.SetColor( GUIColourPalette::gPalette->GetTextColour( eBase ) );
      windowApp.Draw( fMCInfoText );
    }
}
