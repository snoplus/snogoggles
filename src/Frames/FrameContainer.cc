#include <SFML/Window/Event.hpp>

#include <Viewer/FrameContainer.hh>
#include <Viewer/TopBar.hh>
#include <Viewer/FrameOutline.hh>
#include <Viewer/Frame.hh>
#include <Viewer/Event.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Button.hh>
using namespace Viewer;

FrameContainer::FrameContainer( RectPtr rect )
  : fRect( rect )
{

}

FrameContainer::~FrameContainer()
{
  delete fFrame;
  delete fTopBar;
  delete fFrameOutline;
  delete fResizeButton;
}

FrameEvent 
FrameContainer::NewEvent( const Event& event )
{
  FrameEvent returnEvent;
  switch( event.type )
    {
    case sf::Event::LostFocus:
      returnEvent = fTopBar->NewEvent( event );
      if( !fResizeButton->NewEvent( event ).IsNULL() )
        returnEvent = FrameEvent( FrameEvent::eStopResize );
      break;
    case sf::Event::MouseButtonReleased:
      // Mouse must be down to move
      returnEvent = FrameEvent( FrameEvent::eStopMove );
      if( fResizeButton->ContainsPoint( event.GetPos() ) )
        return FrameEvent( FrameEvent::eStopResize );
    case sf::Event::MouseButtonPressed:
      if( fResizeButton->ContainsPoint( event.GetPos() ) )
        return FrameEvent( FrameEvent::eStartResize );
    case sf::Event::MouseMoved:
      if( fTopBar->ContainsPoint( event.GetPos() ) )
        {
          returnEvent = fTopBar->NewEvent( event );
          return returnEvent;
        }
      else
        fTopBar->NewEvent( Event( sf::Event::LostFocus ) );
      if( fResizeButton->ContainsPoint( event.GetPos() ) )
        fResizeButton->NewEvent( event );
      else
        fTopBar->NewEvent( Event( sf::Event::LostFocus ) );
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
FrameContainer::PreInitialise( const ConfigurationTable* configTable )
{
  fTopBar = new TopBar( RectPtr( fRect->NewDaughter() ) );
  fTopBar->PreInitialise( configTable );
  fFrameOutline = new FrameOutline( RectPtr( fRect->NewDaughter() ) );
  fFrameOutline->PreInitialise( configTable );
  fResizeButton = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 0 );
  fResizeButton->Initialise( 5 );
  SetRect( fRect->GetRect( Rect::eResolution ), Rect::eResolution );
  fFrame->PreInitialise( configTable );
  if( configTable != NULL )
    {
      sf::Rect<double> posRect;
      posRect.left = configTable->GetD( "x" );
      posRect.top = configTable->GetD( "y" );
      posRect.width = configTable->GetD( "width" );
      posRect.height = configTable->GetD( "height" );
      SetRect( posRect, Rect::eLocal );
    }
}

void 
FrameContainer::PostInitialise( const ConfigurationTable* configTable )
{
  fTopBar->PostInitialise( configTable );
  fFrame->PostInitialise( configTable );
}

void 
FrameContainer::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetS( "type", fFrame->GetName() ); // Loaded in FrameManager!
  sf::Rect<double> posRect = fRect->GetRect( Rect::eLocal );
  configTable->SetD( "x", posRect.left );
  configTable->SetD( "y", posRect.top );
  configTable->SetD( "width", posRect.width );
  configTable->SetD( "height", posRect.height );
  fTopBar->SaveConfiguration( configTable );
  fFrame->SaveConfiguration( configTable );
}

void
FrameContainer::ProcessEvent( const RenderState& renderState )
{
  fFrame->ProcessEvent( renderState );
}

void
FrameContainer::ProcessRun()
{
  fFrame->ProcessRun();
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
  fFrame->RenderGUI( renderApp, renderState );
  fFrameOutline->RenderGUI( renderApp );
  fTopBar->RenderGUI( renderApp );
  fResizeButton->Render( renderApp );
}

void
FrameContainer::SetRect( const sf::Rect<double>& rect,
                         const Rect::ECoordSystem& system )
{
  fRect->SetRect( rect, system );
  // The top bar is always 20 high, so ensure this
  const sf::Rect<double> size = fRect->GetRect( Rect::eResolution );
  sf::Rect<double> topBarSize = size;
  topBarSize.height = 20.0;
  fTopBar->SetRect( topBarSize );
  sf::Rect<double> outlineSize = size;
  outlineSize.top += 20.0;
  outlineSize.height -= 20.0;
  fFrameOutline->SetRect( outlineSize );
  /// Now the frame rect 2 pxl margin at base
  sf::Rect<double> frameSize = size;
  frameSize.height -= 22.0;
  frameSize.top += 20.0;
  fFrame->GetRect()->SetRect( frameSize, Rect::eResolution );
  sf::Rect<double> resizeSize = size;
  resizeSize.left = size.left + size.width - 20.0;
  resizeSize.top = size.top + size.height - 20.0;
  resizeSize.height = 20.0;
  resizeSize.width = 20.0;
  fResizeButton->GetRect()->SetRect( resizeSize, Rect::eResolution );
}

bool
FrameContainer::IsPinned()
{
  return fTopBar->IsPinned();
}

double
FrameContainer::GetAspectRatio() const
{
  return fFrame->GetAspectRatio();
}

