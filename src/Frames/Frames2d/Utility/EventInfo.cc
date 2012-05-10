#include <RAT/DS/EV.hh>

#include <SFML/Graphics/Rect.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/EventInfo.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/EV.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Frames;

EventInfo::~EventInfo()
{

}

void 
EventInfo::Initialise()
{
  Frame::Initialise();
  sf::Rect<double> textSize;
  textSize.Left = 0.0; textSize.Top = 0.0; textSize.Width = 1.0; textSize.Height = 1.0;
  fInfoText = new Text( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  string hello("Hello");
  fInfoText->SetString( hello );
  fInfoText->SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
}

void 
EventInfo::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}
void 
EventInfo::Render2d( RWWrapper& renderApp,
		     const RenderState& renderState )
{
  stringstream eventInfo;
  eventInfo.precision( 0 );
  eventInfo << fixed;

  DataStore& events = DataStore::GetInstance();
  const RIDS::Event& event = events.GetCurrentEvent();
  eventInfo << "GTID: " << event.GetEV().GetGTID() << endl;
  /*eventInfo << "Time: " << rEV->GetUTDays() << "d " << rEV->GetUTSecs() << "s" << endl;
  eventInfo << "Trigger: " << ToHexString( rEV->GetTrigType() ) << endl;
  eventInfo << "Esum int/peak/diff: " << rEV->GetESumInt() << "/" << rEV->GetESumPeak() << "/" << rEV->GetESumDiff() << endl;
  eventInfo << "Data Clean: " << ToHexString( rEV->GetDataCleanFlags() ) << endl;
  eventInfo << "Nhit: " << rEV->GetPMTAllCalCount() << endl;
  eventInfo << "Nhit (Cal): " << rEV->GetPMTCalCount() << endl;
  eventInfo << "Nhit (UnCal): " << rEV->GetPMTUnCalCount() << endl;
  eventInfo << "Nhit (OWL): " << rEV->GetPMTOWLCalCount() << endl;
  eventInfo << "Nhit (LG): " << rEV->GetPMTLGCalCount() << endl;
  eventInfo << "Nhit (Neck): " << rEV->GetPMTNeckCalCount() << endl;
  eventInfo << "Nhit (FECD): " << rEV->GetPMTFECDCalCount() << endl;
  eventInfo << "Nhit (Spare): " << rEV->GetPMTSpareCalCount() << endl;
  eventInfo << "Nhit (Inv): " << rEV->GetPMTInvCalCount() << endl;
  */
  fInfoText->SetString( eventInfo.str() );
  fInfoText->SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  renderApp.Draw( *fInfoText );  
}

string
EventInfo::ToByteString( int number )
{
  stringstream byteStream;
  for( size_t iLoop = 1; iLoop <= sizeof(int) * 8; iLoop++ )
    {    
      const int val = number >> ( sizeof(int) * 8 - iLoop );
      if( val & 1 )
	byteStream << "1";
      else
	byteStream << "0";
      if( iLoop % 4 == 0 )
	byteStream << " ";
    }
  return byteStream.str();
}

string
EventInfo::ToHexString( int number )
{
  stringstream hexStream;
  hexStream << hex << uppercase;
  hexStream << "0x" << number;
  return hexStream.str();
}
