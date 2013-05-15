#include <Viewer/ButtonLabel.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

void 
ButtonLabel::Initialise( unsigned int textureNumber,
                         const std::string& label,
                         bool fixed )
{
  Button::Initialise( textureNumber );
  fText.SetString( label );
  if( fixed )
    fText.SetCharSize( GUIProperties::GetInstance().GetTextSize() );
}

void 
ButtonLabel::Render( RWWrapper& renderApp )
{
  Button::Render( renderApp );
  renderApp.Draw( fText );
}
