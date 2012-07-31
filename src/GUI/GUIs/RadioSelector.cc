#include <SFML/Graphics/Rect.hpp>

using namespace std;

#include <Viewer/RadioSelector.hh>
#include <Viewer/PersistLabel.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

RadioSelector::RadioSelector( RectPtr rect,
                              unsigned int guiID )
  : GUI( rect, guiID ), fGUIManager( rect )
{

}

RadioSelector::~RadioSelector()
{

}

void 
RadioSelector::Initialise( const vector<string>& options )
{
  sf::Rect<double> fullSize = fRect->GetRect( Rect::eResolution );
  const double rowHeight = fullSize.height / static_cast<double>( options.size() ); 
  const double rowSpacing = 2.0;

  sf::Rect<double> size;
  size.left = fullSize.left;
  size.width = fullSize.width;
  size.height = rowHeight - rowSpacing;
  for( int iLabel = 0; iLabel < options.size(); iLabel++ )
    {
      size.top = rowHeight * iLabel + fullSize.top;
      fPersistLabels.push_back( fGUIManager.NewGUI<GUIs::PersistLabel>( size, Rect::eResolution ) );
      dynamic_cast<GUIs::PersistLabel*>( fGUIManager.GetGUI( iLabel ) )->Initialise( 12, options[iLabel] );
    }
  SetState( 0 );
}

void 
RadioSelector::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}

GUIEvent 
RadioSelector::NewEvent( const Event& event )
{
  GUIEvent eventReturned = fGUIManager.NewEvent( event );
  if( !eventReturned.IsNULL() )
    {
      SetState( eventReturned.fguiID );
      return GUIEvent( fID, fGlobalID );
    }
  return GUIEvent();
}

void 
RadioSelector::SetState( unsigned int state )
{
  for( unsigned int iLabel = 0; iLabel < fPersistLabels.size(); iLabel++ )
    if( iLabel != state )
      fPersistLabels[iLabel]->SetState( false );
    else
      fPersistLabels[iLabel]->SetState( true );
}

unsigned int
RadioSelector::GetState() const 
{
  for( unsigned int iLabel = 0; iLabel < fPersistLabels.size(); iLabel++ )
    if( fPersistLabels[iLabel]->GetState() )
      return iLabel;
  return 0;
}
