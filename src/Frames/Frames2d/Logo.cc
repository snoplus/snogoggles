#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>
using namespace std;

#include <Viewer/Logo.hh>
#include <Viewer/TextureManager.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>
using namespace Viewer;
using namespace Viewer::Frames;

Logo::~Logo()
{
  delete fLogo, fMessage;
}

void
Logo::Initialise()
{
  Frame::Initialise();
  TextureManager& textureManager = TextureManager::GetInstance();
  fTextures[0] = textureManager.GetTexture( "Logo.png" );
  fTextures[1] = textureManager.GetTexture( "Logo2.png" );
  
  sf::Rect<double> spriteSize = fRect->GetRect( Rect::eLocal );
  spriteSize.Width = 0.5;
  spriteSize.Height = 0.5;
  fLogo = new Sprite( RectPtr( fRect->NewDaughter( spriteSize, Rect::eLocal ) ) );
  sf::Rect<double> textSize = spriteSize;
  textSize.Left = 0.5;
  fMessage = new Text( RectPtr( fRect->NewDaughter( textSize, Rect::eLocal ) ) );
  string hello("Hello");
  fMessage->SetString( hello );
  fState = false;
}

void
Logo::LoadConfiguration( ConfigurationTable& configTable )
{
  sf::Rect<double> button( 0.8, 0.1, 0.2, 0.1 );
  
  try
    {
      fState = configTable.GetI( "state" );
    }
  catch( ConfigurationTable::NoAttributeError& e )
    {
      // Oh dear
    }
  try
    {
      //if( configTable.GetTable( "Nested" )->GetI( "state" ) )
      //fMessage.SetString( "BOB" );
    }
  catch( ConfigurationTable::NoTableError& e )
    {
      // Ah well
    }
}

void
Logo::SaveConfiguration( ConfigurationTable& configTable )
{
  configTable.SetI( "state", fState );
  ConfigurationTable* newTable = configTable.NewTable( "Nested" );
  newTable->SetI( "state", 0 );
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
Logo::Render2d( RWWrapper& renderApp,
		const RenderState& renderState )
{
  if( fState )
    fLogo->SetTexture( fTextures[0] );
  else
    fLogo->SetTexture( fTextures[1] );
  renderApp.Draw( *fLogo );
  renderApp.Draw( *fMessage );
}
