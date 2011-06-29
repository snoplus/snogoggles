#include <Viewer/FrameManager.hh>
#include <Viewer/FrameContainer.hh>
#include <Viewer/FrameCoord.hh>
using namespace Viewer;

void 
FrameManager::Initialise( ConfigurationTable& configTable )
{
  // Temp init 
  FrameContainer* logoFrame = new FrameContainer();
  logoFrame->Initialise( configTable );
  // Very Temp
  FrameCoord a;
  a.SetFrameRect( sf::Rect<double>( 100, 100, 200, 100 ) );
  logoFrame->SetContainerCoord( a );
  fFrames.push_back( logoFrame );
}
  
void 
FrameManager::NewEvent( sf::Event& event )
{
  // TODO
}

void 
FrameManager::RenderGUI( sf::RenderWindow& windowApp )
{
  for( unsigned int uFrame = 0; uFrame < fFrames.size(); uFrame++ )
    fFrames[uFrame]->RenderGUI( windowApp );
}

void 
FrameManager::Render2d( sf::RenderWindow& windowApp )
{
  for( unsigned int uFrame = 0; uFrame < fFrames.size(); uFrame++ )
    fFrames[uFrame]->Render2d( windowApp );
}

void 
FrameManager::Render3d( sf::RenderWindow& windowApp )
{
  for( unsigned int uFrame = 0; uFrame < fFrames.size(); uFrame++ )
    fFrames[uFrame]->Render3d( windowApp );
}
  
void 
FrameManager::SaveConfiguration( ConfigurationTable& configTable )
{
  for( unsigned int uFrame = 0; uFrame < fFrames.size(); uFrame++ )
    fFrames[uFrame]->SaveConfiguration( configTable );
}
