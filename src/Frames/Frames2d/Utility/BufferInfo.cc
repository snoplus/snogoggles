#include <SFML/Graphics/Rect.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/BufferInfo.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Frames;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/Time.hh>

BufferInfo::~BufferInfo()
{

}

void 
BufferInfo::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> textSize;
  textSize.left = 0.0; textSize.top = 0.0; textSize.width = 1.0; textSize.height = 1.0;
  fInfoText = new Text( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  string hello("Hello");
  fInfoText->SetString( hello );
  fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetB( eBase ) );
}

void 
BufferInfo::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}
void 
BufferInfo::Render2d( RWWrapper& renderApp,
		     const RenderState& renderState )
{
  stringstream eventInfo;
  eventInfo.precision( 0 );
  eventInfo << fixed;
  eventInfo << "Input Buffer:" << endl;
  eventInfo << "\tSize:" << DataStore::GetInstance().GetInputBufferSize() << endl;
  eventInfo << "\tWaiting elements:" << DataStore::GetInstance().GetBufferElements() << endl;

  eventInfo << "Buffer:" << endl;
  eventInfo << "\tSize:" << DataStore::GetInstance().GetBufferSize() << endl;
  eventInfo << "\tEvents Added:" << DataStore::GetInstance().GetEventsAdded() << endl;

  const RIDS::Event& event = DataStore::GetInstance().GetCurrentEvent();
  eventInfo << "Current Event:" << endl;
  eventInfo << "Recieved Time: " << event.GetTime().GetTime() << endl;

  fInfoText->SetString( eventInfo.str() );
  fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  renderApp.Draw( *fInfoText );  
}

string
BufferInfo::ToByteString( int number )
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
BufferInfo::ToHexString( int number )
{
  stringstream hexStream;
  hexStream << hex << uppercase;
  hexStream << "0x" << number;
  return hexStream.str();
}
