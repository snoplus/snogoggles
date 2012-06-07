#include <SFML/Window/Event.hpp>

#include <sstream>
using namespace std;

#include <Viewer/FramePanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/ButtonLabel.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/FrameManager.hh>
using namespace Viewer;

FramePanel::FramePanel( RectPtr rect,
                        RectPtr frameRect,
                        FrameManager& frameManager )
  : Panel( rect, "FramePanel" ), fFrameManager( frameManager ), fFrameFactory( frameRect )
{
 
}

FramePanel::~FramePanel()
{

}

void
FramePanel::EventLoop()
{
  vector<string> frameNames = fFrameFactory.GetNames();

  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID >= 10 )
        { 
          Frame* newFrame = fFrameFactory.New( frameNames[fEvents.front().fguiID - 10] );
          fFrameManager.NewFrame( newFrame );
        }
      fEvents.pop();
    }
}

void 
FramePanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
}

void
FramePanel::PostInitialise( const ConfigurationTable* configTable )
{

}

void
FramePanel::LoadGUIConfiguration( const ConfigurationTable* config )
{
  for( unsigned int uGUIs = 0; uGUIs < config->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = config->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) )
        {
          sf::Rect<double> posRect( objectConfig->GetD( "x" ), objectConfig->GetD( "y" ), objectConfig->GetD( "width" ), objectConfig->GetD( "height" ) );
          //fGUIs[objectConfig->GetI( "effect" )]  = fGUIManager.NewGUI< GUIs::Persist >( posRect, objectConfig->GetI( "effect" ) );
          //dynamic_cast<GUIs::Persist*>( fGUIs[objectConfig->GetI( "effect" )] )->Initialise( 12 );
        }
    }
  // Build the new frame buttons
  const ConfigurationTable* areaConfig = config->GetTable( "frameButtonArea" );
  sf::Rect<double> fullArea = fRect->GetRect( Rect::eResolution );
  sf::Rect<double> buttonArea( areaConfig->GetD( "x" ) * fullArea.Width + fullArea.Left, 
                               areaConfig->GetD( "y" ) * fullArea.Height + fullArea.Top, 
                               areaConfig->GetD( "width" ) * fullArea.Width, 
                               areaConfig->GetD( "height" ) * fullArea.Height );
  const double rowHeight = 20.0; const double colWidth = 120.0;
  const double rowSpacing = 2.0; const double colSpacing = 2.0;
  const int numRows = buttonArea.Height / ( rowHeight + rowSpacing );
  const int numCols = buttonArea.Width / ( colWidth + colSpacing );

  sf::Rect<double> size;
  size.Width = colWidth;
  size.Height = rowHeight;
  vector<string> frameNames = fFrameFactory.GetNames();
  for( int iFrame = 0; iFrame < frameNames.size(); iFrame++ )
    {

      size.Left = ( colWidth + colSpacing ) * ( iFrame / numRows ) + buttonArea.Left;
      size.Top = ( rowHeight + rowSpacing ) * ( iFrame % numRows ) + buttonArea.Top;
      GUIs::ButtonLabel* temp = fGUIManager.NewGUI<GUIs::ButtonLabel>( size, iFrame + 10, Rect::eResolution );
      temp->Initialise( 2, frameNames[iFrame] );
    }

}

void
FramePanel::SaveConfiguration( ConfigurationTable* configTable )
{

}
