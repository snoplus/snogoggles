using namespace std;

#include <Viewer/DataStore.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/ChannelList.hh>
#include <Viewer/RIDS/FibreList.hh>

size_t 
AdjustIndex( const size_t currentIndex, 
             const size_t limit, 
             const int change )
{
  if( limit == 1 )
    return 0;
  if( change > 0 )
    return ( currentIndex + change ) % limit;
  else
    {
      int newIndex = currentIndex + change;
      if( newIndex < 0 )
        newIndex = limit + newIndex;
      return newIndex;
    }
}


DataStore::DataStore()
  : fInputBuffer( 5000 ) 
{ 
  fEvents.resize( 60000, NULL ); 
  fWrite = 0;
  fRead = 0;
  fEventsAdded = 0;
}

void
DataStore::Initialise()
{
  Update();
}

DataStore::~DataStore()
{
  Update();
  for( unsigned int uLoop = 0; uLoop < fEvents.size(); uLoop++ )
    delete fEvents[uLoop];
  fEvents.clear();
  for( map<int, RIDS::ChannelList*>::iterator iTer = fChannelLists.begin(); iTer != fChannelLists.end(); iTer++ )
    delete iTer->second;
  fChannelLists.clear();
  for( map<int, RIDS::FibreList*>::iterator iTer = fFibreLists.begin(); iTer != fFibreLists.end(); iTer++ )
    delete iTer->second;
  fFibreLists.clear();
}

bool 
DataStore::AddEvent( RIDS::Event* event )
{
  return fInputBuffer.Push( event );
}

void 
DataStore::Update()
{
  /// This will overwrite existing events
  RIDS::Event* currentEvent = NULL;
  while( fInputBuffer.Pop( currentEvent ) )
    {
      fEventsAdded++;
      delete fEvents[fWrite];
      const int runID = currentEvent->GetRunID();
      if( fChannelLists.count( runID ) == 0 )
        {
          RIDS::ChannelList* channelList = new RIDS::ChannelList();
          channelList->Initialise( runID );
          fChannelLists[runID] = channelList;
        }
      if( fFibreLists.count( runID ) == 0 )
        {
          RIDS::FibreList* fibreList = new RIDS::FibreList();
          fibreList->Initialise( runID );
          fFibreLists[runID] = fibreList;
        }
      fEvents[fWrite] = currentEvent;
      fWrite = AdjustIndex( fWrite, fEvents.size(), 1 );
    }
}

void 
DataStore::Move( RIDS::Event* event,
                 RIDS::ChannelList* channelList,
                 RIDS::FibreList* fibreList,
                 int step )
{
  if( fEventsAdded > fEvents.size() )
    fRead = AdjustIndex( fRead, fEvents.size(), step );
  else
    fRead = AdjustIndex( fRead, fEventsAdded, step );
  *event = *fEvents[fRead]; // Copy it over
  *channelList = *fChannelLists[event->GetRunID()]; // Copy it over
  *fibreList = *fFibreLists[event->GetRunID()]; // Copy it over
}

RIDS::Event*
DataStore::Peek( int step )
{
  if( step <= -min( fEventsAdded, static_cast<int>( fEvents.size() ) ) )
    return NULL;
  if( fEventsAdded > fEvents.size() )
    return fEvents[AdjustIndex( fRead, fEvents.size(), step )];
  else
    return fEvents[AdjustIndex( fRead, fEventsAdded, step )];
}
