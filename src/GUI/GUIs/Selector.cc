#include <SFML/Graphics/Rect.hpp>

using namespace std;

#include <Viewer/Selector.hh>
#include <Viewer/GUIImageButton.hh>
#include <Viewer/Text.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIColourPalette.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

Selector::~Selector()
{
  delete fNext, fPrev, fText;
}

void 
Selector::Initialise( const vector<string>& labels )
{
  sf::Rect<double> size;
  size.Left = 0.0; size.Top = 0.0; size.Width = 1.0; size.Height = 1.0;
  fOptions = labels;
  size.Left = 0.9;
  size.Width = 0.1;
  fNext = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) , 0 );
  fNext->Initialise( eIncrease );
  size.Left = 0.0;
  fPrev = new GUIs::GUIImageButton( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) , 1 );
  fPrev->Initialise( eDecrease );
  size.Left = 0.1; size.Width = 0.8;
  fText = new Text( RectPtr( fRect->NewDaughter( size, Rect::eLocal ) ) );
  fCurrentOption = 0;
  fText->SetString( fOptions[fCurrentOption] );
}

void 
Selector::Render( RWWrapper& renderApp )
{
  fNext->Render( renderApp );
  fPrev->Render( renderApp );
  fText->SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
  renderApp.Draw( *fText );
}

GUIEvent 
Selector::NewEvent( const Event& event )
{
  GUIEvent retEvent; // Defaul NULL
  // Broadcast lost focus events to all, otherwise find which to broadcast to
  if( event.Type == sf::Event::MouseButtonReleased )
    {
      if( fNext->ContainsPoint( event.GetPos() ) )
	fCurrentOption = ( fCurrentOption + 1 ) % fOptions.size();
      else if( fPrev->ContainsPoint( event.GetPos() ) )
	fCurrentOption = ( fCurrentOption - 1 ) % fOptions.size();
      retEvent = GUIEvent( fID, fGlobalID );
    }
  fText->SetString( fOptions[fCurrentOption] );
  return retEvent;
}

unsigned int
Selector::GetState() const
{
  return fCurrentOption;
}
