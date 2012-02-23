using namespace std;

#include <SFML/Graphics/Texture.hpp>

#include <Viewer/CheckBoxLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUITextureManager.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/Sprite.hh>
#include <Viewer/Text.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

CheckBoxLabel::CheckBoxLabel( RectPtr rect, 
			      unsigned int guiID )
  : Persist( rect, guiID )
{
  GUITextureManager& textureManager = GUITextureManager::GetInstance();
  fBoxTextures[0] = textureManager.GetTexture( eOpenBox, eBase );
  fBoxTextures[1] = textureManager.GetTexture( eCrossBox, eHighlight );


  sf::Rect<double> size = rect->GetRect( Rect::eResolution );
  sf::Rect<double> buttonSize = size;
  buttonSize.Width = size.Height;
  sf::Rect<double> textSize = size;
  textSize.Width = size.Width - buttonSize.Width;
  textSize.Left = buttonSize.Width + size.Left;
  fBox = new Sprite( RectPtr( fRect->NewDaughter( buttonSize, Rect::eResolution ) ) );
  fLabel = new Text( RectPtr( fRect->NewDaughter( textSize, Rect::eResolution ) ) );
  string temp( "Check Box" );
  fLabel->SetString( temp );
}

CheckBoxLabel::~CheckBoxLabel()
{
  delete fBox, fLabel;
}

void
CheckBoxLabel::SetLabel( const string& label )
{
  fLabel->SetString( label );
}

#include <iostream>
using namespace std;
void 
CheckBoxLabel::Render( RWWrapper& renderApp )
{
  if( !fPressed )
    fBox->SetTexture( fBoxTextures[0] );
  else
    fBox->SetTexture( fBoxTextures[1] );

  renderApp.Draw( *fBox );
  fLabel->SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  renderApp.Draw( *fLabel );
}
