#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/About.hh>
using namespace Viewer;
using namespace Frames;

void 
About::Initialise()
{
  fInfoText = Text( "SNOGoggles v0.1" );
  fInfoText.SetColor( sf::Color( 0, 0, 0 ) );
  fInfoText.SetBoundingRect( sf::Rect<double>( 0.1, 0.1, 0.8, 0.25 ) );  
}

void 
About::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}
void 
About::Render2d( RWWrapper& windowApp )
{
  stringstream eventInfo;
  eventInfo << "SNOGoggles v0.1" << "\nFrame Rate:";
  if( windowApp.GetFrameTime() == 0 ) // Damn quick system...
    eventInfo << "> 1000 Hz";
  else
    eventInfo << 1e3 / (double) windowApp.GetFrameTime() << " Hz";
  fInfoText.SetString( eventInfo.str().c_str() );
  windowApp.Draw( fInfoText );  
}
