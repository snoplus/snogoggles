#include <string>
using namespace std;

#include <Viewer/FrameMasterUI.hh>
#include <Viewer/NewFrameButton.hh>
#include <Viewer/FrameManager.hh>
using namespace Viewer;

FrameMasterUI::FrameMasterUI( RectPtr rect,
			      RectPtr frameMotherRect,
			      FrameManager* frameManager )
  : fRect( rect ), fFrameManager( frameManager ), fGUIManager( rect ), fFrameFactory( frameMotherRect )
{

}

void
FrameMasterUI::NewEvent( const Event& event )
{
  GUIEvent guiEvent = fGUIManager.NewEvent( event );
  if( guiEvent.IsNULL() == false )
    fEvents.push( guiEvent );
}

void 
FrameMasterUI::EventLoop()
{
  vector<string> frameNames = fFrameFactory.GetNames();
  while( !fEvents.empty() )
    {
      Frame* newFrame = fFrameFactory.New( frameNames[fEvents.front().fguiID] );
      fFrameManager->NewFrame( newFrame );
      fEvents.pop();
    }
}

void 
FrameMasterUI::SaveConfiguration( ConfigurationTable* configTable )
{

}

void 
FrameMasterUI::PreInitialise( const ConfigurationTable* configTable )
{
  // Decide the sizes first
  const double rowHeight = 20.0; const double colWidth = 120.0;
  const double rowSpacing = 2.0; const double colSpacing = 2.0;
  sf::Rect<double> fullSize = fRect->GetRect( Rect::eResolution );
  const int numRows = fullSize.Height / ( rowHeight + rowSpacing );
  const int numCols = fullSize.Width / ( colWidth + colSpacing );

  sf::Rect<double> size;
  size.Width = colWidth;
  size.Height = rowHeight;
  vector<string> frameNames = fFrameFactory.GetNames();
  for( int iFrame = 0; iFrame < frameNames.size(); iFrame++ )
    {

      size.Left = ( colWidth + colSpacing ) * ( iFrame / numRows ) + fullSize.Left;
      size.Top = ( rowHeight + rowSpacing ) * ( iFrame % numRows ) + fullSize.Top;
      fButtons.push_back( fGUIManager.NewGUI<GUIs::NewFrameButton>( size, Rect::eResolution ) );
      fButtons[iFrame]->Initialise( frameNames[iFrame] );
    }
}

void 
FrameMasterUI::PostInitialise( const ConfigurationTable* configTable )
{
  // load current desktop
}

void 
FrameMasterUI::Render( RWWrapper& renderApp )
{
  fGUIManager.Render( renderApp );
}
