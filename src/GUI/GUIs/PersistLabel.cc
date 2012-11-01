using namespace std;

#include <SFML/Graphics/Texture.hpp>

#include <Viewer/PersistLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

PersistLabel::PersistLabel( RectPtr rect, 
                            unsigned int guiID )
  : GUI( rect, guiID ), fPersist( RectPtr( rect->NewDaughter() ), guiID ), fText( RectPtr( rect->NewDaughter() ) )
{
  sf::Rect<double> size = rect->GetRect( Rect::eResolution );
  sf::Rect<double> buttonSize = size;
  buttonSize.width = size.height;
  sf::Rect<double> textSize = size;
  textSize.width = size.width - buttonSize.width;
  textSize.left = buttonSize.width + size.left;
  fPersist.GetRect()->SetRect( buttonSize, Rect::eResolution );
  fText.GetRect()->SetRect( textSize, Rect::eResolution );
  string temp( "Check Box" );
  fText.SetString( temp );
}

PersistLabel::~PersistLabel()
{

}

void
PersistLabel::Initialise( unsigned int textureNumber,
                          const string& label )
{
  fPersist.Initialise( textureNumber );
  fText.SetString( label );
}

void
PersistLabel::SetLabel( const string& label )
{
  fText.SetString( label );
}

GUIEvent 
PersistLabel::NewEvent( const Event& event )
{
  return fPersist.NewEvent( event );
}

void 
PersistLabel::Render( RWWrapper& renderApp )
{
  fPersist.Render( renderApp );
  fText.SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  renderApp.Draw( fText );
}
