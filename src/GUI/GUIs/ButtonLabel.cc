#include <Viewer/ButtonLabel.hh>
#include <Viewer/RWWrapper.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

void 
ButtonLabel::Initialise( unsigned int textureNumber,
                         const std::string& label )
{
  Button::Initialise( textureNumber );
  fText.SetString( label );
}

void 
ButtonLabel::Render( RWWrapper& renderApp )
{
  Button::Render( renderApp );
  renderApp.Draw( fText );
}
