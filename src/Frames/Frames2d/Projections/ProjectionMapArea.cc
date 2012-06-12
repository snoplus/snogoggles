#include <cmath>
#include <sstream>
using namespace std;

#include <Viewer/ProjectionMapArea.hh>
#include <Viewer/MapArea.hh>
#include <Viewer/HitInfo.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/DataStore.hh>
using namespace Viewer;
using namespace Viewer::Frames;

ProjectionMapArea::~ProjectionMapArea()
{
  delete fHitInfo;
}

void 
ProjectionMapArea::PostInitialise( const ConfigurationTable* configTable )
{
  ProjectionBase::PostInitialise( configTable );
  sf::Rect<double> size;
  size.Left = 0.025; size.Top = 0.0; size.Width = 0.95; size.Height = 0.95;
  ProjectionBase::Initialise( size );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( size );
  size.Left = 0.05; size.Top = 0.95; size.Width = 0.9; size.Height = 0.05;
  fHitInfo = new HitInfo( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ), true );
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
	  const double closeRadius = 0.005;
	  if( fabs( fProjectedPMTs[ipmt].x - mousePos.x ) < closeRadius && fabs( fProjectedPMTs[ipmt].y - mousePos.y ) < closeRadius )
	    fPMTofInterest = ipmt;
	}
      fEvents.pop();
    }
}

void
ProjectionMapArea::Render2d( RWWrapper& renderApp,
			     const RenderState& renderState )
{
  ProjectionBase::Render2d( renderApp, renderState );
  if( fPMTofInterest != -1 )
    fHitInfo->Render( renderApp, renderState, fPMTofInterest );
}
