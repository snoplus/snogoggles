#include <SFML/Graphics/Rect.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/EventInfo.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/RenderState.hh>
using namespace Viewer;
using namespace Frames;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/Time.hh>

EventInfo::~EventInfo()
{

}

void 
EventInfo::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> textSize;
  textSize.left = 0.0; textSize.top = 0.0; textSize.width = 1.0; textSize.height = 1.0;
  fInfoText = new Text( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  string hello("Hello");
  fInfoText->SetString( hello );
  fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetB( eBase ) );
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

  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  eventInfo << "Run :" << event.GetRunID() << endl;
  eventInfo << "Sub Run :" << event.GetSubRunID() << endl;
  eventInfo << "Event GTID :" << event.GetEventID() << endl;
  eventInfo << "Trigger :" << TriggerToString( event.GetTrigger() ) << endl;

  const vector<string> sourceNames = RIDS::Event::GetSourceNames();
  for( size_t source = 0; source < sourceNames.size(); source++ )
    {
      eventInfo << sourceNames[source] << ":" << endl;
      const vector<string> typeNames = RIDS::Event::GetTypeNames( source );
      for( size_t type = 0; type < typeNames.size(); type++ )
        eventInfo << typeNames[type] << ": " << event.GetSource( source ).GetType( type ).GetCount() << ", ";
      eventInfo << endl;
    }
  fInfoText->SetString( eventInfo.str() );
  fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
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

string
EventInfo::TriggerToString( int trigger )
{
  // This code needs improving and generalising for snogoggles! PGJ
  stringstream triggerStream;
  if( trigger == 0x0 )
    triggerStream << "ORPH";
  if( trigger & 0x01 )
    triggerStream << "100L,";
  if( trigger & 0x02 )
    triggerStream << "100M,";
  if( trigger & 0x04 )
    triggerStream << "10HL,";
  if( trigger & 0x08 )
    triggerStream << "20,";
  if( trigger & 0x10 )
    triggerStream << "20L,";
  if( trigger & 0x20 )
    triggerStream << "ESUML,";
  if( trigger & 0x40 )
    triggerStream << "ESUMH,";
  if( trigger & 0x80 )
    triggerStream << "OWL,";
  if( trigger & 0x100 )
    triggerStream << "OWLL,";
  if( trigger & 0x200 )
    triggerStream << "OWLH,";
  if( trigger & 0x400 )
    triggerStream << "PUL,";
  if( trigger & 0x800 )
    triggerStream << "PRE,";
  if( trigger & 0x1000 )
    triggerStream << "PED,";
  if( trigger & 0x2000 )
    triggerStream << "PONG,";
  if( trigger & 0x4000 )
    triggerStream << "SYNC,";
  if( trigger & 0x8000 )
    triggerStream << "EXT,";
  return triggerStream.str();
}
