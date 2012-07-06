#include <SFML/Window/Event.hpp>
using namespace std;

#include <Viewer/EventPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Button.hh>
#include <Viewer/RadioSelector.hh>
#include <Viewer/SlideSelector.hh>
using namespace Viewer;

EventPanel::EventPanel( RectPtr rect )
  : Panel( rect, "EventPanel" )
{
  fRenderState.ChangeState( RIDS::eCal, RIDS::eTAC ); /// TEMP
  fEventPeriod = -1.0;
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
      else if( event.Key.Code == sf::Keyboard::P )
        {
          fEventPeriod = -1.0;
          dynamic_cast<GUIs::SlideSelector*>( fGUIs[4] )->SetState( 0.0 );
        }
      else if( event.Key.Code == sf::Keyboard::I )
        {
          fEventPeriod = 0.0;
          dynamic_cast<GUIs::SlideSelector*>( fGUIs[4] )->SetState( 0.95 );
        }
    }
  Panel::NewEvent( event );
}

void
EventPanel::EventLoop()
{
  fRenderState.Reset(); // Reset the changed information
  DataStore::GetInstance().Reset();
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
        case 2: // Source change
        case 3: // Type change
          fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[2] )->GetEnumState<RIDS::EDataSource>(), 
                                    dynamic_cast<GUIs::RadioSelector*>( fGUIs[3] )->GetEnumState<RIDS::EDataType>() );
          break;
        case 4: // Change in event display rate
          double slideScale = dynamic_cast<GUIs::SlideSelector*>( fGUIs[4] )->GetState();
          if( slideScale <= 0.1 )
            fEventPeriod = -1.0;
          else if( slideScale >= 0.95 )
            fEventPeriod = 0.0;
          else
            {
              fEventPeriod = 0.5 / slideScale;
              fClock.Restart();
            }
          break;
        }
      fEvents.pop();
    }
  // Manage the continuous event switching
  if( fEventPeriod == 0.0 )
    events.Latest();
  if( fEventPeriod > 0.0 && fClock.GetElapsedTime().AsSeconds() > fEventPeriod )
    {
      events.Next();
      fClock.Restart();
    }
}

void 
EventPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
  if( configTable != NULL )
    {
      dynamic_cast<GUIs::RadioSelector*>( fGUIs[2] )->SetState( configTable->GetI( "data_source" ) );
      dynamic_cast<GUIs::RadioSelector*>( fGUIs[3] )->SetState( configTable->GetI( "data_type" ) );
    }
  fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[2] )->GetEnumState<RIDS::EDataSource>(), 
                            dynamic_cast<GUIs::RadioSelector*>( fGUIs[3] )->GetEnumState<RIDS::EDataType>() );
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
          switch( effect )
            {
            case 0:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 11 );
              break;
            case 1:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 10 );
              break;
            case 2:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::RadioSelector >( posRect, effect );
                vector<string> sourceOptions;
                dynamic_cast<GUIs::RadioSelector*>( fGUIs[effect] )->Initialise( RenderState::GetSourceStrings() );
              }
              break;
            case 3:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::RadioSelector >( posRect, effect );
                dynamic_cast<GUIs::RadioSelector*>( fGUIs[effect] )->Initialise( RenderState::GetTypeStrings() );
              }
              break;
            case 4:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::SlideSelector >( posRect, effect );
                vector<double> stops; stops.push_back( 0.0 ); stops.push_back( 0.25 ); stops.push_back( 0.6 ); stops.push_back( 0.95 );
                dynamic_cast<GUIs::SlideSelector*>( fGUIs[effect] )->Initialise( stops );
              }
              break;
            }
          
        }
    }
}

void
EventPanel::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "data_source", dynamic_cast<GUIs::RadioSelector*>( fGUIs[2] )->GetState() );
  configTable->SetI( "data_type", dynamic_cast<GUIs::RadioSelector*>( fGUIs[3] )->GetState() );
}
