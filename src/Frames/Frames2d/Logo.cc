#include <SFML/Graphics.hpp>

#include <Viewer/Logo.hh>
#include <Viewer/ImageManager.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/CheckBoxLabel.hh>
using namespace Viewer;
using namespace Frames;

void
Logo::Initialise( ConfigurationTable& configTable )
{
  ImageManager& imageManager = ImageManager::GetInstance();
  fLogo = imageManager.NewSprite( "Logo.png" );
  fLogo.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 1.0, 1.0 ) );
  fLogo2 = imageManager.NewSprite( "Logo2.png" );
  fLogo2.SetBoundingRect( sf::Rect<double>( 0.0, 0.0, 0.5, 0.5 ) );
  fMessage = Text( "Hello" );
  fMessage.SetBoundingRect( sf::Rect<double>( 0.5, 0.0, 0.5, 0.5 ) );
  fMessage.SetColor( sf::Color( 0, 0, 0 ) );
  fState = false;
  sf::Rect<double> button( 0.8, 0.1, 0.2, 0.1 );
  GUIs::CheckBoxLabel* cbLabel = dynamic_cast<GUIs::CheckBoxLabel*>( fGUIManager.NewGUI<GUIs::CheckBoxLabel>( button ) );
  cbLabel->SetLabel( "New Logo" );

  fState = configTable.GetI( "state" );
  cbLabel->SetState( fState );
}

void
Logo::SaveConfiguration( ConfigurationTable& configTable )
{
  configTable.SetI( "state", fState );
}

void 
Logo::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID == 0 )
	fState = !fState;
      fEvents.pop();
    }
}
void 
Logo::Render2d( RWWrapper& windowApp )
{
  if( fState )
    windowApp.Draw( fLogo );
  else
    windowApp.Draw( fLogo2 );
  windowApp.Draw( fMessage );
}
