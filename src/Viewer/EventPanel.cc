#include <SFML/Window/Event.hpp>

using namespace std;

#include <Viewer/EventPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Button.hh>
#include <Viewer/DataStore.hh>
using namespace Viewer;

EventPanel::EventPanel( RectPtr rect )
  : Panel( rect, "EventPanel" )
{
  fRenderState.ChangeState( RIDS::eCal, RIDS::eTAC ); /// TEMP
}

EventPanel::~EventPanel()
{

}

void
EventPanel::NewEvent( const Event& event )
{
  DataStore& events = DataStore::GetInstance();
  if( event.Type == sf::Event::KeyPressed )
    {
      if( event.Key.Code == sf::Keyboard::Right )
        events.Next();
      else if( event.Key.Code == sf::Keyboard::Left )
        events.Prev();
    }
  Panel::NewEvent( event );
}

void
EventPanel::EventLoop()
{
  DataStore& events = DataStore::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Previous
          events.Prev();
          break;
        case 1: // Next
          events.Next();
          break;
        }
      fEvents.pop();
    }
}

void 
EventPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
}

void
EventPanel::PostInitialise( const ConfigurationTable* configTable )
{

}

void
EventPanel::LoadGUIConfiguration( const ConfigurationTable* config )
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
              fGUIs[effect]  = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 10 );
            }
          else if( effect == 1 )
            {
              fGUIs[effect]  = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 11 );
            }
        }
    }
}

void
EventPanel::SaveConfiguration( ConfigurationTable* configTable )
{

}
