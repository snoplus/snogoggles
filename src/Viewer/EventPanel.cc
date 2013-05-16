#include <SFML/Window/Event.hpp>

#include <sstream>
using namespace std;

#include <Viewer/EventPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/Button.hh>
#include <Viewer/RadioSelector.hh>
#include <Viewer/SlideSelector.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/TextBox.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>


EventPanel::EventPanel( RectPtr rect )
  : Panel( rect, "EventPanel" )
{
  fRenderState.ChangeState( 0, 0 );
  fLatest = false;
  fEventPeriod = -1.0;
}

EventPanel::~EventPanel()
{

}

void
EventPanel::NewEvent( const Event& event )
{
  DataSelector& eventSelector = DataSelector::GetInstance();
  if( GUI::fsKeyboardFocus == -1 && event.type == sf::Event::KeyPressed )
    {
      if( event.key.code == sf::Keyboard::Right )
        eventSelector.Move( 1 );
      else if( event.key.code == sf::Keyboard::Left )
        eventSelector.Move( -1 );
      else if( event.key.code == sf::Keyboard::P )
        {
          ChangeRateMode( -1.0, false );
        }
      else if( event.key.code == sf::Keyboard::I )
        {
          ChangeRateMode( -1.0, true );
        }
      else if( event.key.code == sf::Keyboard::C )
        {
          ChangeRateMode( 0.0, false );
        }
    }
  Panel::NewEvent( event );
}

void
EventPanel::EventLoop()
{
  fRenderState.Reset(); // Reset the changed information
  DataSelector& eventSelector = DataSelector::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case eMultiPrev:
          eventSelector.Move( -10 );
          break;
        case eMultiNext:
          eventSelector.Move( 10 );
          break;
        case ePrev: // Previous
          eventSelector.Move( -1 );
          break;
        case eNext: // Next
          eventSelector.Move( +1 );
          break;
        case eIDInput:
          {
            stringstream input( dynamic_cast<GUIs::TextBox*>( fGUIs[eIDInput] )->GetString() );
            int id; input >> id;
            eventSelector.MoveToID( id );
          }
          break;
        case eDataSource: // Source change
          fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->GetState(), 0 );
          dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->Initialise( DataSelector::GetInstance().GetTypeNames( fRenderState.GetDataSource() ), true );
          break;
        case eDataType: // Type change
          fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->GetState(),
                                    dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->GetState() );
          break;
        case eRate: // Change in event display rate
          {
            double slideScale = dynamic_cast<GUIs::SlideSelector*>( fGUIs[eRate] )->GetState();
            double period = 0.5 / slideScale;
            if( slideScale <= 0.1 )
              period = -1.0;
            else if( slideScale >= 0.95 )
              period = 0.0;
            ChangeRateMode( period, false );
          }
          break;
        case eLatest:
          {
            ChangeRateMode( -1.0, dynamic_cast<GUIs::PersistLabel*>( fGUIs[eLatest] )->GetState() );
          }
          break;
        }
      fEvents.pop();
    }
  // Manage the continuous event switching
  if( fLatest )
    eventSelector.Latest();
  else if( !fLatest && fEventPeriod == 0.0 )
    eventSelector.Move( 1 );
  else if( !fLatest && fEventPeriod > 0.0 && fClock.getElapsedTime().asSeconds() > fEventPeriod )
    {
      eventSelector.Move( 1 );
      fClock.restart();
    }
}

void 
EventPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
  if( configTable != NULL )
    {
      dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->SetState( configTable->GetI( "data_source" ) );
      dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->SetState( configTable->GetI( "data_type" ) );
      dynamic_cast<GUIs::SlideSelector*>( fGUIs[eRate] )->SetState( configTable->GetD( "event_rate_scale" ) );
    }
  fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->GetState(),
                            dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->GetState() );
}

void
EventPanel::PostInitialise( const ConfigurationTable* configTable )
{
  dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->Initialise( RIDS::Event::GetSourceNames(), true );
  dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->Initialise( RIDS::Event::GetTypeNames( fRenderState.GetDataSource() ), true );
}

void
EventPanel::LoadGUIConfiguration( const ConfigurationTable* config )
{
  for( unsigned int uGUIs = 0; uGUIs < config->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = config->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) )
        {
          sf::Rect<double> posRect = LoadRect( objectConfig, fRect );
          int effect = objectConfig->GetI( "effect" );
          switch( effect )
            {
            case eMultiPrev: 
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 32 );
              break;
            case ePrev: 
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 34 );
              break;
            case eNext:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 35 );
              break;
            case eMultiNext:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 33 );
              break;
            case eDataSource:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::RadioSelector >( posRect, effect );
              break;
            case eDataType:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::RadioSelector >( posRect, effect );
              break;
            case eRate:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::SlideSelector >( posRect, effect );
                vector<double> stops; stops.push_back( 0.0 ); stops.push_back( 0.25 ); stops.push_back( 0.6 ); stops.push_back( 0.95 );
                dynamic_cast<GUIs::SlideSelector*>( fGUIs[effect] )->Initialise( stops );
              }
              break;
            case eLatest:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::PersistLabel >( posRect, effect );
                dynamic_cast<GUIs::PersistLabel*>( fGUIs[effect] )->Initialise( 16, "Latest" );
              }
              break;
            case eIDInput:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::TextBox >( posRect, effect );
              break;
            }
        }
    }
}

void
EventPanel::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "data_source", dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->GetState() );
  configTable->SetI( "data_type", dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->GetState() );
  configTable->SetD( "event_rate_scale", dynamic_cast<GUIs::SlideSelector*>( fGUIs[eRate] )->GetState() );
}

void
EventPanel::ChangeRateMode( double period, bool latest )
{
  fEventPeriod = period;
  fLatest = latest;
  dynamic_cast<GUIs::PersistLabel*>( fGUIs[eLatest] )->SetState( latest );
  if( period < 0.0 )
    dynamic_cast<GUIs::SlideSelector*>( fGUIs[eRate] )->SetState( 0.0 );
  if( period == 0.0 )
    dynamic_cast<GUIs::SlideSelector*>( fGUIs[eRate] )->SetState( 0.95 );
  fClock.restart();
}
