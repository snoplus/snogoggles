#include <SFML/Window/Event.hpp>

#include <sstream>
using namespace std;

#include <Viewer/FramePanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/ButtonLabel.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/FrameManager.hh>
#include <Viewer/FrameFactory.hh>
using namespace Viewer;

FramePanel::FramePanel( RectPtr rect,
                        RectPtr frameRect,
                        FrameManager& frameManager )
  : Panel( rect, "FramePanel" ), fFrameManager( frameManager )
{
 
}

FramePanel::~FramePanel()
{

}

void
FramePanel::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( fEvents.front().fguiID >= 10 )
        { 
          fFrameManager.NewFrame( dynamic_cast<GUIs::ButtonLabel*>( fGUIs[fEvents.front().fguiID] )->GetLabel() );
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
  sf::Rect<double> buttonArea( areaConfig->GetD( "x" ) * fullArea.width + fullArea.left, 
                               areaConfig->GetD( "y" ) * fullArea.height + fullArea.top, 
                               areaConfig->GetD( "width" ) * fullArea.width, 
                               areaConfig->GetD( "height" ) * fullArea.height );
  const double rowHeight = 20.0; const double colWidth = 120.0;
  const double rowSpacing = 2.0; const double colSpacing = 2.0;
  const int numRows = buttonArea.height / ( rowHeight + rowSpacing );
  const int numCols = buttonArea.width / ( colWidth + colSpacing );

  sf::Rect<double> size;
  size.width = colWidth;
  size.height = rowHeight;
  FrameFactory frameFactory;
  vector<string> frameNames = frameFactory.GetNames();
  for( int iFrame = 0; iFrame < frameNames.size(); iFrame++ )
    {

      size.left = ( colWidth + colSpacing ) * ( iFrame / numRows ) + buttonArea.left;
      size.top = ( rowHeight + rowSpacing ) * ( iFrame % numRows ) + buttonArea.top;
      fGUIs[iFrame + 10] = fGUIManager.NewGUI<GUIs::ButtonLabel>( size, iFrame + 10, Rect::eResolution );
      dynamic_cast<GUIs::ButtonLabel*>( fGUIs[iFrame + 10] )->Initialise( 36, frameNames[iFrame] );
    }

}

void
FramePanel::SaveConfiguration( ConfigurationTable* configTable )
{

}
