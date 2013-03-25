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
///     22/03/13 : P.Jones - New RIDS refactor.\n
///
/// \detail  Holds RIDS::Event events and the RAT::DS::Run data. 
///          Also has an index to the current DS event and then the 
///          current sub ev event.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_DataStore__
#define __Viewer_DataStore__

#include <vector>

#include <Viewer/InputBuffer.hh>

#include <Viewer/RIDS/Channel.hh>
#include <Viewer/RIDS/ChannelList.hh>

namespace Viewer
{
namespace RIDS
{
  class Event;
}

class DataStore
{
public:
  static DataStore& GetInstance();

  void Initialise();

  virtual ~DataStore();
  /// Set the current run
  void SetRun( int runID );
  /// Add an event to the structure (data thread only)
  bool Add( RIDS::Event& event );
  /// Move to the latest event
  void Latest();
  /// Move to the next event, rolls over
  void Next( const size_t step = 1 );
  /// Move to the previous event, rolls over
  void Prev( const size_t step = 1 );

  inline const RIDS::Event& GetCurrentEvent() const;
  inline bool HasChanged() const;
  /// Update the data structure, fetch events from input buffer
  void Update();

  int GetInputBufferSize() const { return fInputBuffer.GetSize(); }
  int GetBufferElements() const { return fInputBuffer.GetNumElements(); }
  int GetBufferSize() const { return fEvents.size(); }
  int GetEventsAdded() const { return fEventsAdded; }

  /// Convienience method
  const std::vector<RIDS::Channel>& GetChannelData( int source, int type ) const;

  inline const RIDS::ChannelList& GetChannelList() const;

  /// Set the analysis state
  void SetAnalysing( const bool state ) { fAnalysing = state; }
  /// Set the selection state
  void SetEventSelecting( const bool state ) { fSelecting = state; }

private:
  /// Run the event over the script and return true if selected
  bool SelectEvent( RIDS::Event* event );
  /// Change the event and run analysis if required
  void ChangeEvent( const size_t eventID );

  InputBuffer<RIDS::Event*> fInputBuffer; /// < The input buffer, events arrive here
  std::vector<RIDS::Event*> fEvents; /// < The event buffer for rendering
  RIDS::Event* fEvent; /// < The currently rendered event
  size_t fRead; /// < The currently read position in fEvents
  size_t fWrite; /// < The current write position in fEvents
  RIDS::ChannelList fChannelList; /// < The information about the channels pos etc...
  int fEventsAdded; /// < Count of added events 
  int fRunID; /// < Current Run ID

  bool fAnalysing;
  bool fSelecting;
  bool fChanged;

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

inline const RIDS::Event&
DataStore::GetCurrentEvent() const
{
  return *fEvent;
}

inline const RIDS::ChannelList& 
DataStore::GetChannelList() const
{
  return fChannelList;
}

inline bool
DataStore::HasChanged() const
{
  return fChanged;
}

} //::Viewer

#endif
