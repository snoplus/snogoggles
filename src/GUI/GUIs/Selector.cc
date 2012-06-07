using namespace std;

#include <SFML/Graphics/Texture.hpp>

#include <Viewer/Selector.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

Selector::Selector( RectPtr rect, 
                    unsigned int guiID )
  : GUI( rect, guiID ), fText( RectPtr( rect->NewDaughter() ) ), fGUIManager( rect )
{
  sf::Rect<double> size = rect->GetRect( Rect::eResolution );
  sf::Rect<double> textSize = size;
  textSize.Width = size.Width - 2.0 * size.Height;
  textSize.Left = size.Height + size.Left;
  fText.GetRect()->SetRect( textSize, Rect::eResolution );
  string temp( "Check Box" );
  fText.SetString( temp );
}

Selector::~Selector()
{

}

void
Selector::Initialise( vector<string> options )
{
  fOptions = options;
}

GUIEvent 
Selector::NewEvent( const Event& event )
{
  return fGUIManager.NewEvent( event );
}

void 
Selector::Render( RWWrapper& renderApp )
{

  fText.SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  renderApp.Draw( fText );
}
