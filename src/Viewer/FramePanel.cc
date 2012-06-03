#include <SFML/Window/Event.hpp>

using namespace std;

#include <Viewer/FramePanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Selector.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/FrameSelector.hh>
using namespace Viewer;

FramePanel::FramePanel( RectPtr rect,
                        FrameManager& frameManager )
  : Panel( rect, "FramePanel" ), fFrameManager( frameManager ), fFrameFactory( rect )
{

}

FramePanel::~FramePanel()
{

}

void
FramePanel::EventLoop()
{
  DataStore& events = DataStore::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // New Frame clicked
          dynamic_cast<GUIs::FrameSelector*>( fGUIs[0] )->GetFrameName();
          break;
        case 1: // Delete all?
          break;
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
          int effect = objectConfig->GetI( "effect" );
          if( effect == 0 )
            {
              fGUIs[effect]  = fGUIManager.NewGUI< GUIs::FrameSelector >( posRect, effect );
              dynamic_cast<GUIs::FrameSelector*>( fGUIs[effect] )->Initialise( fFrameFactory.GetNames() );
            }
          else if( effect == 1 )
            {
              //fGUIs[effect] = fGUIManager.NewGUI< GUIs::GUIImageButton >( posRect, effect );
            }
        }
    }
}

void
FramePanel::SaveConfiguration( ConfigurationTable* configTable )
{

}
