////////////////////////////////////////////////////////////////////////
/// \class DataStore
///
/// \brief   Holds all the available current data.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     12/05/11 : P.Jones - First Revision, new file. \n
///     27/02/12 : P.Jones - Second Revision, replace old version, 
///                hopefully more stable. \n
///     22/04/12 : P.Jones - Add scripting ability. \n
///     07/05/12 : P.Jones - Renamed, refactored to use RIDS.
///     02/07/12 : O.Wasalski - Added method for frames to check whether
///                the current event being displayed has changed. \n
///     17/10/12 : P.Jones - New buffering system.\n
///     22/03/13 : P.Jones - New RIDS refactor. Split into DataStore and
///                DataSelector. \n
///
/// \detail  This class holds all the RIDS::Events and all the ChannelLists
///          A DataSelector chooses which event to show. This is a 
///          singleton class.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_DataStore__
#define __Viewer_DataStore__

#include <vector>
#include <map>

#include <Viewer/InputBuffer.hh>

namespace Viewer
{
namespace RIDS
{
  class Event;
  class ChannelList;
  class FibreList;
}

class DataStore
{
public:
  /// Singleton class instance
  static DataStore& GetInstance();
  /// Initialise the DataStore, post semaphore
  void Initialise();
  /// Destory the DataStore
  virtual ~DataStore();
  /// Add an event, this is called by the Data Thread ONLY, return true on success
  bool AddEvent( RIDS::Event* event );
  /// Update, moves events from the input buffer to the available buffer
  void Update();
  /// Move to the event step away
  void Move( RIDS::Event* event, 
             RIDS::ChannelList* channelList,
             RIDS::FibreList* fibreList,
             int step );
  /// Peek at the event step away
  RIDS::Event* Peek( int step );
  /// Information functions
  size_t GetInputBufferSize() const { return fInputBuffer.GetSize(); }
  size_t GetBufferElements() const { return fInputBuffer.GetNumElements(); }
  size_t GetBufferSize() const { return fEvents.size(); }
  size_t GetEventsAdded() const { return fEventsAdded; }
private:
  InputBuffer<RIDS::Event*> fInputBuffer; /// < The input buffer, events arrive here
  std::map<int, RIDS::ChannelList*> fChannelLists; /// < ChannelLists mapped by run ID
  std::map<int, RIDS::FibreList*> fFibreLists; /// < FibreLists mapped by run ID
  std::vector<RIDS::Event*> fEvents; /// < The event buffer for rendering
  size_t fRead; /// < The currently read position in fEvents
  size_t fWrite; /// < The current write position in fEvents
  int fEventsAdded; /// < Count of added events 

  /// Prevent usage of methods below
  DataStore();
  DataStore( DataStore& );
  void operator=( DataStore& );
};

inline DataStore&
DataStore::GetInstance()
{
  static DataStore eventData;
  return eventData;
}

} //::Viewer

#endif
