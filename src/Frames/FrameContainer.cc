#include <Viewer/FrameContainer.hh>
#include <Viewer/Frame.hh>
#include <Viewer/Logo.hh>
using namespace Viewer;

void 
FrameContainer::Initialise( ConfigurationTable& configTable )
{
  fFrame = new Frames::Logo();
  fFrame->Initialise( configTable );
}
  
void 
FrameContainer::Render2d( sf::RenderWindow& windowApp )
{
  fFrame->Render2d( windowApp );
}

void 
FrameContainer::Render3d( sf::RenderWindow& windowApp )
{
  fFrame->Render3d( windowApp );
}

void 
FrameContainer::RenderGUI( sf::RenderWindow& windowApp )
{
  fFrame->RenderGUI( windowApp );
}

void 
FrameContainer::NewEvent( sf::Event& event )
{
  fFrame->NewEvent( event );
}
  
void 
FrameContainer::SaveConfiguration( ConfigurationTable& configTable )
{
  fFrame->SaveConfiguration( configTable );
}


void 
FrameContainer::SetContainerCoord( FrameCoord& frameCoord )
{
  fContainerCoord = frameCoord;
  // Chop off top and pass to frame
  fFrame->SetFrameCoord( frameCoord );
}
