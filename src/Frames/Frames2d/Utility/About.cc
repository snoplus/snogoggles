#include <SFML/Graphics/Rect.hpp>

#include <sstream>
#include <string>
using namespace std;

#include <Viewer/About.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Frames;

About::~About()
{
  delete fInfoText;
}

void 
About::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> textSize;
  textSize.left = 0.0; textSize.top = 0.0; textSize.width = 1.0; textSize.height = 1.0;
  fInfoText = new Text( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  string hello("Hello");
  fInfoText->SetString( hello );
  fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  fFrameRates.resize( 10, 0.0 );
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
  fFrameRates.push_back( (double) renderApp.GetFrameTime().asMicroseconds() );
  fFrameRates.pop_front();
  double averageRate = 0.0;
  for( deque<double>::const_iterator iTer = fFrameRates.begin(); iTer != fFrameRates.end(); iTer++ )
    averageRate += *iTer;
  eventInfo << 1e6 * fFrameRates.size() / averageRate << " Hz";
  if( GUIProperties::GetInstance().HasChanged() )
    fInfoText->SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  fInfoText->SetString( eventInfo.str() );
  renderApp.Draw( *fInfoText );  
}
