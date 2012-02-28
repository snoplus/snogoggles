#include <SFML/Window/Event.hpp>

#include <Viewer/FrameContainer.hh>
#include <Viewer/TopBar.hh>
#include <Viewer/Frame.hh>
#include <Viewer/Event.hh>
using namespace Viewer;

#include <Viewer/LambertProjection.hh>
#include <Viewer/IcosahedralProjection.hh>
#include <Viewer/CrateView.hh>
#include <Viewer/HitFrame3d.hh>
#include <Viewer/Histogram.hh>

FrameContainer::FrameContainer( RectPtr rect )
  : fRect( rect )
{

}

FrameEvent 
FrameContainer::NewEvent( const Event& event )
{
  FrameEvent returnEvent;
  switch( event.Type )
    {
    case sf::Event::LostFocus:
      returnEvent = fTopBar->NewEvent( event );
      break;
    case sf::Event::MouseButtonReleased:
      // Mouse must be down to move
      returnEvent = FrameEvent( FrameEvent::eStopMove );
    case sf::Event::MouseMoved:
    case sf::Event::MouseButtonPressed:
      if( fTopBar->ContainsPoint( event.GetPos() ) )
	{
	  returnEvent = fTopBar->NewEvent( event );
	  return returnEvent;
	}
      // Do NOT CONTINUE if the event is destined for the top bar
      break;
    }
  fFrame->NewEvent( event );
  return returnEvent;
}

void 
FrameContainer::EventLoop()
{
  fFrame->EventLoop();
}

void 
FrameContainer::SaveConfiguration( ConfigurationTable& configTable )
{

}

void 
FrameContainer::Initialise( Frame* frame )
{
  fTopBar = new TopBar( RectPtr( fRect->NewDaughter() ) );
  fTopBar->Initialise();
  fFrame = frame;
  fFrame->NewMother( RectPtr( fRect->NewDaughter() ) );
  fFrame->Initialise();
  SetRect( fRect->GetRect( Rect::eResolution ), Rect::eResolution );
}

void 
FrameContainer::LoadConfiguration( ConfigurationTable& configTable )
{

}

void 
FrameContainer::Render2d( RWWrapper& renderApp, 
			  const RenderState& renderState )
{
  fFrame->Render2d( renderApp, renderState );
}

void 
FrameContainer::Render3d( RWWrapper& renderApp, 
			  const RenderState& renderState )
{
  fFrame->Render3d( renderApp, renderState );
}

void 
FrameContainer::RenderGUI( RWWrapper& renderApp, 
			   const RenderState& renderState )
{
  fTopBar->RenderGUI( renderApp );
  fFrame->RenderGUI( renderApp, renderState );
}

void
FrameContainer::SetRect( const sf::Rect<double>& rect,
			 const Rect::ECoordSystem& system )
{
  sf::Rect<double> size = rect;
  fRect->SetRect( size, system );
  // The top bar is always 20 high, so ensure this
  size = fRect->GetRect( Rect::eResolution );
  const double height = size.Height;
  size.Height = 20.0;
  fTopBar->SetRect( size );
  /// Now the frame rect 2 pxl margin at base
  size.Height = height - 22.0;
  size.Top += 20.0;
  fFrame->GetRect()->SetRect( size, Rect::eResolution );
}

bool
FrameContainer::IsPinned()
{
  fTopBar->IsPinned();
}
