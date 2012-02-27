#include <cmath>
#include <sstream>
using namespace std;

#include <Viewer/ProjectionMapArea.hh>
#include <Viewer/MapArea.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::Frames;

ProjectionMapArea::~ProjectionMapArea()
{
  delete fInfoText;
}

void 
ProjectionMapArea::Initialise()
{
  sf::Rect<double> size;
  size.Left = 0.05; size.Top = 0.0; size.Width = 0.9; size.Height = 0.9;
  ProjectionBase::Initialise( size );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( size );
  size.Top = 0.9;
  fInfoText = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
}

void 
ProjectionMapArea::EventLoop()
{
  while( !fEvents.empty() )
    {
      // Only one event type is likely
      sf::Vector2<double> mousePos = fMapArea->GetPosition();
      if( mousePos.x < 0.0 )
	{
	  fEvents.pop();
	  continue;
	}
      // Now know it is a true move event
      fPMTofInterest = -1;
      for( unsigned int ipmt = 0; ipmt < fProjectedPMTs.size(); ipmt++ )
	{
	  if( fabs( fProjectedPMTs[ipmt].x - mousePos.x ) < 0.01 && fabs( fProjectedPMTs[ipmt].y - mousePos.y ) < 0.01 )
	    fPMTofInterest = ipmt;
	}
      fEvents.pop();
    }
}

void
ProjectionMapArea::Render2d( RWWrapper& renderApp,
			     const RenderState& renderState )
{
  stringstream info;
  info << fPMTofInterest;
  fInfoText->SetString( info.str() );
  renderApp.Draw( *fInfoText );
}
