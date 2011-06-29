#include <SFML/Graphics.hpp>

#include <Viewer/Logo.hh>
#include <Viewer/ImageManager.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;
using namespace Frames;

void
Logo::Initialise( ConfigurationTable& configTable )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fLogo = imageManager.NewSprite( "Logo.png" );
}

void
Logo::SaveConfiguration( ConfigurationTable& configTable )
{
  // Nothing TODO
}

void 
Logo::EventLoop()
{
  // Nothing TODO
}
void 
Logo::Render2d( sf::RenderWindow& windowApp )
{
  sf::Rect<double> frameRect = fFrameCoord.GetFrameRect();
  fLogo.Resize( frameRect.Width, frameRect.Height );
  fLogo.SetPosition( frameRect.Left, frameRect.Top );
  windowApp.Draw( fLogo );
}
