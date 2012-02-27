#include <SFML/Graphics/Rect.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/About.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Frames;

About::~About()
{
  delete fInfoText;
}

void 
About::Initialise()
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
About::EventLoop()
{
  while( !fEvents.empty() )
    {
      fEvents.pop();
    }
}
void 
About::Render2d( RWWrapper& renderApp,
		 const RenderState& renderState )
{
  stringstream eventInfo;
  eventInfo.precision( 0 );
  eventInfo << fixed;
  eventInfo << "SNOGoggles Air Fill" << "\nFrame Rate:";
  eventInfo << 1e6 / (double) renderApp.GetFrameTime().AsMicroseconds() << " Hz";
  fInfoText->SetString( eventInfo.str() );
  fInfoText->SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  renderApp.Draw( *fInfoText );  
}
