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
#include <Viewer/ScalingBar.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/PythonScripts.hh>
using namespace Viewer;

EventPanel::EventPanel( RectPtr rect )
  : Panel( rect, "EventPanel" )
{
  fRenderState.ChangeState( RIDS::eCal, RIDS::eTAC ); /// TEMP
  fLatest = false;
  fEventPeriod = -1.0;
}

EventPanel::~EventPanel()
{

}

void
EventPanel::NewEvent( const Event& event )
{
  DataStore& events = DataStore::GetInstance();
  if( GUI::fsKeyboardFocus == -1 && event.type == sf::Event::KeyPressed )
    {
      if( event.key.code == sf::Keyboard::Right )
        events.Next();
      else if( event.key.code == sf::Keyboard::Left )
        events.Prev();
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
  DataStore& events = DataStore::GetInstance();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case eMultiPrev:
          events.Prev( 10 );
          break;
        case eMultiNext:
          events.Next( 10 );
          break;
        case ePrev: // Previous
          events.Prev();
          break;
        case eNext: // Next
          events.Next();
          break;
        case eDataSource: // Source change
        case eDataType: // Type change
          fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->GetEnumState<RIDS::EDataSource>(), 
                                    dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->GetEnumState<RIDS::EDataType>() );
          dynamic_cast<GUIs::ScalingBar*>( fGUIs[eScaling] )->Reset();
          if( fRenderState.GetDataSource() == RIDS::eScript )
            dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->SetOptions( PythonScripts::GetInstance().GetAnalysis().GetDataLabels() );
          else
            dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->SetOptions( RenderState::GetTypeStrings() );
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
        case eScaling: // Change in scaling
          fRenderState.ChangeScaling( dynamic_cast<GUIs::ScalingBar*>( fGUIs[eScaling] )->GetMin(),
                                      dynamic_cast<GUIs::ScalingBar*>( fGUIs[eScaling] )->GetMax() );
          break;
        }
      fEvents.pop();
    }
  // Manage the continuous event switching
  if( fLatest )
    events.Latest();
  else if( !fLatest && fEventPeriod == 0.0 )
    events.Next();
  else if( !fLatest && fEventPeriod > 0.0 && fClock.getElapsedTime().asSeconds() > fEventPeriod )
    {
      events.Next();
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
      dynamic_cast<GUIs::ScalingBar*>( fGUIs[eScaling] )->SetState( configTable->GetD( "scale_min" ),
                                                                    configTable->GetD( "scale_max" ) );
      dynamic_cast<GUIs::SlideSelector*>( fGUIs[eRate] )->SetState( configTable->GetD( "event_rate_scale" ) );
    }
  fRenderState.ChangeState( dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataSource] )->GetEnumState<RIDS::EDataSource>(), 
                            dynamic_cast<GUIs::RadioSelector*>( fGUIs[eDataType] )->GetEnumState<RIDS::EDataType>() );
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
            case eMultiPrev: 
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 30 );
              break;
            case ePrev: 
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 11 );
              break;
            case eNext:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 10 );
              break;
            case eMultiNext:
              fGUIs[effect] = fGUIManager.NewGUI< GUIs::Button >( posRect, effect );
              dynamic_cast<GUIs::Button*>( fGUIs[effect] )->Initialise( 31 );
              break;
            case eDataSource:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::RadioSelector >( posRect, effect );
                dynamic_cast<GUIs::RadioSelector*>( fGUIs[effect] )->Initialise( RenderState::GetSourceStrings() );
              }
              break;
            case eDataType:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::RadioSelector >( posRect, effect );
                dynamic_cast<GUIs::RadioSelector*>( fGUIs[effect] )->Initialise( RenderState::GetTypeStrings() );
              }
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
                dynamic_cast<GUIs::PersistLabel*>( fGUIs[effect] )->Initialise( 14, "Force Latest?" );
              }
              break;
            case eScaling:
              {
                fGUIs[effect] = fGUIManager.NewGUI< GUIs::ScalingBar >( posRect, effect );
              }
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
  configTable->SetD( "scale_min", dynamic_cast<GUIs::ScalingBar*>( fGUIs[eScaling] )->GetMin() );
  configTable->SetD( "scale_max", dynamic_cast<GUIs::ScalingBar*>( fGUIs[eScaling] )->GetMax() );
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
