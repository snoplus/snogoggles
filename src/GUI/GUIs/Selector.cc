using namespace std;

#include <Viewer/Selector.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/Button.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

Selector::Selector( RectPtr rect, 
                    unsigned int guiID )
  : GUI( rect, guiID ), fText( RectPtr( rect->NewDaughter() ) ), fGUIManager( rect ), fBackground( RectPtr( rect->NewDaughter() ) )
{
  fState = 0;
  /// Initialise the text, left button, right button and background in that order
  sf::Rect<double> size = rect->GetRect( Rect::eResolution );
  const double buttonWidth = size.height; // Button size is defined by height
  sf::Rect<double> textSize = size;
  textSize.width = size.width - 2.0 * buttonWidth;
  textSize.left = buttonWidth + size.left;
  fText.GetRect()->SetRect( textSize, Rect::eResolution );
  sf::Rect<double> buttonSize = size;
  buttonSize.width = buttonWidth;
  GUIs::Button* temp = fGUIManager.NewGUI< GUIs::Button >( buttonSize, Rect::eResolution );
  temp->Initialise( 20 );
  buttonSize.left = size.left + size.width - buttonWidth;
  temp = fGUIManager.NewGUI< GUIs::Button >( buttonSize, Rect::eResolution );
  temp->Initialise( 21 );
  size.left = size.left + buttonWidth;
  size.width = size.width - 2.0 * buttonWidth;
  fBackground.GetRect()->SetRect( size, Rect::eResolution );
  const GUITextureManager& textureManager = GUIProperties::GetInstance().GetGUITextures();
  fBackground.SetTexture( textureManager.GetTexture( 22, eBase ) );
}

Selector::~Selector()
{

}

void
Selector::Initialise( const vector<string>& options )
{
  fOptions = options;
}

GUIEvent 
Selector::NewEvent( const Event& event )
{
  GUIEvent returnedEvent = fGUIManager.NewEvent( event );
  if( !returnedEvent.IsNULL() )
    {
      if( returnedEvent.fguiID == 0 ) // Next option
        fState = ( fState + 1 ) % fOptions.size();
       if( returnedEvent.fguiID == 1 ) // Prev option
        fState = ( fState - 1 ) % fOptions.size();
       return GUIEvent( fID, fGlobalID );
    }
  return GUIEvent();
}

void 
Selector::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
  renderApp.Draw( fBackground );
  fText.SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  if( !fOptions.empty() )
    fText.SetString( fOptions[fState] );
  renderApp.Draw( fText );
}
