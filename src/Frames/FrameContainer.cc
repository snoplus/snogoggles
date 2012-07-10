#include <SFML/Window/Event.hpp>

#include <Viewer/FrameContainer.hh>
#include <Viewer/TopBar.hh>
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
  delete fResizeButton;
}

FrameEvent 
FrameContainer::NewEvent( const Event& event )
{
  FrameEvent returnEvent;
  switch( event.Type )
    {
    case sf::Event::LostFocus:
      returnEvent = fTopBar->NewEvent( event );
      if( !fResizeButton->NewEvent( event ).IsNULL() )
        return FrameEvent( FrameEvent::eStopResize );
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
  fResizeButton = new GUIs::Button( RectPtr( fRect->NewDaughter() ), 0 );
  fResizeButton->Initialise( 4 );
  SetRect( fRect->GetRect( Rect::eResolution ), Rect::eResolution );
  fFrame->PreInitialise( configTable );
  if( configTable != NULL )
    {
      sf::Rect<double> posRect;
      posRect.Left = configTable->GetD( "x" );
      posRect.Top = configTable->GetD( "y" );
      posRect.Width = configTable->GetD( "width" );
      posRect.Height = configTable->GetD( "height" );
      SetRect( posRect, Rect::eResolution );
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
  sf::Rect<double> posRect = fRect->GetRect( Rect::eResolution );
  configTable->SetD( "x", posRect.Left );
  configTable->SetD( "y", posRect.Top );
  configTable->SetD( "width", posRect.Width );
  configTable->SetD( "height", posRect.Height );
  fTopBar->SaveConfiguration( configTable );
  fFrame->SaveConfiguration( configTable );
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
  fTopBar->RenderGUI( renderApp );
  fResizeButton->Render( renderApp );
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
  size.Height = 20.0;
  size.Width = 20.0;
  size.Left = rect.Left + rect.Width - 20.0;
  size.Top = rect.Top + rect.Height - 20.0;
  fResizeButton->GetRect()->SetRect( size, Rect::eResolution );
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

void
FrameContainer::SetFrame( Frame* frame )
{
  fFrame = frame;
  fFrame->NewMother( RectPtr( fRect->NewDaughter() ) );
}
