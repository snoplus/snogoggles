#include <RAT/DS/EV.hh>

#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/EventInfo.hh>
#include <Viewer/EventData.hh>
using namespace Viewer;
using namespace Frames;

void 
EventInfo::Initialise()
{
  fInfoText.SetColor( sf::Color( 0, 0, 0 ) );
  fInfoText.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ) );  
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
EventInfo::Render2d( RWWrapper& windowApp )
{
  stringstream eventInfo;
  eventInfo.precision( 0 );
  eventInfo << fixed;

  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();
  eventInfo << "GTID: " << rEV->GetEventID() << endl;
  eventInfo << "Time: " << rEV->GetUTDays() << "d " << rEV->GetUTSecs() << "s" << endl;
  eventInfo << "Trigger: " << ToHexString( rEV->GetTrigType() ) << endl;
  eventInfo << "Esum int/peak/diff: " << rEV->GetESumInt() << "/" << rEV->GetESumPeak() << "/" << rEV->GetESumDiff() << endl;
  eventInfo << "Data Clean: " << ToHexString( rEV->GetDataCleanFlags() ) << endl;
  eventInfo << "Nhit: " << rEV->GetPMTAllCalCount() << endl;
  eventInfo << "Nhit (Cal): " << rEV->GetPMTCalCount() << endl;
  eventInfo << "Nhit (OWL): " << rEV->GetPMTOWLCalCount() << endl;
  eventInfo << "Nhit (LG): " << rEV->GetPMTLGCalCount() << endl;
  eventInfo << "Nhit (Neck): " << rEV->GetPMTNeckCalCount() << endl;
  eventInfo << "Nhit (FECD): " << rEV->GetPMTFECDCalCount() << endl;
  eventInfo << "Nhit (Spare): " << rEV->GetPMTSpareCalCount() << endl;
  eventInfo << "Nhit (Inv): " << rEV->GetPMTInvCalCount() << endl;

  fInfoText.SetString( eventInfo.str().c_str() );
  windowApp.Draw( fInfoText );  
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
