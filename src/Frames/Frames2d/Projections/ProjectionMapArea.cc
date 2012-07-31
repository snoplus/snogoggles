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
  sf::Rect<double> size;
  size.left = 0.025; size.top = 0.0; size.width = 0.95; size.height = 0.95;
  ProjectionBase::Initialise( size );
  fMapArea = fGUIManager.NewGUI<GUIs::MapArea>( size );
  size.left = 0.05; size.top = 0.95; size.width = 0.9; size.height = 0.05;
  fHitInfo = new HitInfo( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ), true );
}

void 
ProjectionMapArea::EventLoop()
{
  while( !fEvents.empty() )
    {
      // Only one event type is likely
      fMousePos = fMapArea->GetPosition();
      // Draw the PMT info as well?
      fPMTofInterest = -1;
      for( unsigned int lcn = 0; lcn < fProjectedPMTs.size(); lcn++ )
        {
          const double closeRadius = 0.005;
          if( fabs( fProjectedPMTs[lcn].x - fMousePos.x ) < closeRadius && fabs( fProjectedPMTs[lcn].y - fMousePos.y ) < closeRadius )
            fPMTofInterest = lcn;
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
