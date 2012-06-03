#include <SFML/Graphics/Rect.hpp>

using namespace std;

#include <Viewer/FrameSelector.hh>
#include <Viewer/NewFrameButton.hh>
using namespace Viewer;
using namespace Viewer::GUIs;

FrameSelector::FrameSelector( RectPtr rect,
                              unsigned int guiID )
  : GUI( rect, guiID ), fGUIManager( rect ), fLastClicked(0)
{

}

FrameSelector::~FrameSelector()
{

}

void 
FrameSelector::Initialise( const vector<string>& frameNames )
{
  const double rowHeight = 20.0; const double colWidth = 120.0;
  const double rowSpacing = 2.0; const double colSpacing = 2.0;
  sf::Rect<double> fullSize = fRect->GetRect( Rect::eResolution );
  const int numRows = fullSize.Height / ( rowHeight + rowSpacing );
  const int numCols = fullSize.Width / ( colWidth + colSpacing );

  sf::Rect<double> size;
  size.Width = colWidth;
  size.Height = rowHeight;
  for( int iFrame = 0; iFrame < frameNames.size(); iFrame++ )
    {
      size.Left = ( colWidth + colSpacing ) * ( iFrame / numRows ) + fullSize.Left;
      size.Top = ( rowHeight + rowSpacing ) * ( iFrame % numRows ) + fullSize.Top;
      fGUIManager.NewGUI<GUIs::NewFrameButton>( size, Rect::eResolution );
      dynamic_cast<GUIs::NewFrameButton*>( fGUIManager.GetGUI( iFrame ) )->Initialise( frameNames[iFrame] );
    }
}

void 
FrameSelector::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}

GUIEvent 
FrameSelector::NewEvent( const Event& event )
{
  GUIEvent eventReturned = fGUIManager.NewEvent( event );
  if( !eventReturned.IsNULL() )
    {
      fLastClicked = eventReturned.fguiID;
      return GUIEvent( fID, fGlobalID );
    }
  return GUIEvent();
}

const std::string 
FrameSelector::GetFrameName() const
{
  return dynamic_cast<NewFrameButton*>( fGUIManager.GetGUI( fLastClicked ) )->GetFrameName();
}
