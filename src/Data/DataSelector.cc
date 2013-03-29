#include <vector>
using namespace std;

#include <Viewer/DataSelector.hh>
#include <Viewer/DataStore.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/ChannelList.hh>

DataSelector::DataSelector()
{
  
}

void 
DataSelector::Initialise()
{
  DataStore& dataStore = DataStore::GetInstance();
  fEvent = new RIDS::Event();
  fChannelList = new RIDS::ChannelList();
  fAnalysisScript.Load( "default" );
  RIDS::Event::SetTypeNames( RIDS::Event::GetSourceNames().size() - 1, fAnalysisScript.GetTypeNames() );
  fEventSelectionScript.Load( "default" );
  dataStore.Move( fEvent, fChannelList, 0 );
  fAnalysisScript.Reset();
  fEvent->SetSource( RIDS::Event::GetSourceNames().size() - 1, fAnalysisScript.GetEvent().GetSource( 0 ) );
}

DataSelector::~DataSelector()
{

}

void
DataSelector::Move( int steps )
{  
  DataStore& dataStore = DataStore::GetInstance();
  int sign = ( 0 < steps ) - ( 0 > steps );
  steps = sign * steps;
  for( size_t step = 0; step < steps; step++ )
    {
      dataStore.Move( fEvent, fChannelList, sign );
      if( fAnalyse && fSelect && fEventSelectionScript.ProcessEvent( *fEvent ) )
        fAnalysisScript.ProcessEvent( *fEvent );
      else if( fAnalyse && !fSelect )
        fAnalysisScript.ProcessEvent( *fEvent );
      if( fSelect && !fEventSelectionScript.ProcessEvent( *fEvent ) )
        {
          steps++;
          if( steps > std::min( dataStore.GetBufferSize(), dataStore.GetEventsAdded() ) )
            dataStore.Move( fEvent, fChannelList, -steps );
        }
    }
  fChanged = true;
  fEvent->SetSource( RIDS::Event::GetSourceNames().size() - 1, fAnalysisScript.GetEvent().GetSource( 0 ) );
}

void 
DataSelector::Latest()
{
  bool advancing = true; // Advancing in time?
  while( advancing )
    {
      RIDS::Time currentTime = fEvent->GetTime();
      Move( +1 );
      if( currentTime > fEvent->GetTime() )
        {
          // No longer advancing, go back a step
          advancing = false;
          Move( -1 );
        }
    }
}

const RIDS::Event& 
DataSelector::GetEvent() const
{
  return *fEvent;
}

const vector<RIDS::Channel>& 
DataSelector::GetData( int source, 
                       int type ) const
{
  return GetEvent().GetData( source, type );
}

const vector<string> 
DataSelector::GetTypeNames( int source ) const
{
  return RIDS::Event::GetTypeNames( source );
}

void 
DataSelector::SetAnalysisScript( const std::string& script )
{
  fAnalysisScript.Load( script );
  RIDS::Event::SetTypeNames( RIDS::Event::GetSourceNames().size() - 1, fAnalysisScript.GetTypeNames() );
  fEvent->SetSource( RIDS::Event::GetSourceNames().size() - 1, fAnalysisScript.GetEvent().GetSource( 0 ) );
}

void 
DataSelector::SetEventSelectionScript( const std::string& script )
{
  fEventSelectionScript.Load( script );
}

