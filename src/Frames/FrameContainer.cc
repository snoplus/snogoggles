#include <SFML/Window/Event.hpp>

#include <Viewer/FrameContainer.hh>
//#include <Viewer/TopBar.hh>
#include <Viewer/Frame.hh>
#include <Viewer/Event.hh>
using namespace Viewer;

FrameContainer::FrameContainer( RectPtr rect )
  : fRect( rect )
{

}

FrameEvent 
FrameContainer::NewEvent( const Event& event )
{
  FrameEvent returnEvent;
  /*switch( event.Type )
    {
    case sf::Event::LostFocus:
      fTopBar.NewEvent( event );
      break;
    case sf::Event::MouseMoved:
    case sf::Event::MouseButtonReleased:
    case sf::Event::MouseButtonPressed:
      if( fTopBar->ContainsPoint( event.GetPos() ) );
	returnEvent = fTopBar->NewEvent( event );
      break;
    }
    fFrame->NewEvent( event );*/
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
FrameContainer::Initialise( const std::string& type )
{
  SetRect( fRect->GetRect( Rect::eResolution ) );
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
  //fTopBar->Render( renderApp );
  fFrame->RenderGUI( renderApp, renderState );
}

void
FrameContainer::SetRect( const sf::Rect<double>& rect )
{
  sf::Rect<double> size = rect;
  fRect->SetRect( size, Rect::eResolution );
  // The top bar is always 20 high, so ensure this
  double temp = size.Height;
  size.Height = 20.0;
  //fTopBar->GetRect()->SetRect( size, Rect::eResolution );
  /// Now the frame rect
  size.Height = temp - 20.0;
  size.Top += 20.0;
  fFrame->GetRect()->SetRect( size, Rect::eResolution );
}

bool
FrameContainer::IsPinned()
{
  return false;//fTopBar->IsPinned();
}
