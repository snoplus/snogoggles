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
#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/PMTHit.hh>

namespace RAT
{
namespace DS
{
  class Root;
  class Run;
}
}

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
  /// Set the run 
  void SetRun( RAT::DS::Run* rRun );
  /// Add a DS event to the structure (data thread only)
  bool Add( RAT::DS::Root* rDS );
  /// Move to the latest event
  void Latest();
  /// Move to the next event, rolls over
  void Next( const size_t step = 1 );
  /// Move to the previous event, rolls over
  void Prev( const size_t step = 1 );

  inline const RIDS::Event& GetCurrentEvent() const;
  /// Get the prev previous event to the latest
  RIDS::Event* GetPreviousEvent( const size_t prev ) const;
  inline RAT::DS::Run& GetRun() const;
  inline bool HasChanged() const;
  /// Update the data structure, fetch events from input buffer
  void Update();

  int GetInputBufferSize() const { return fInputBuffer.GetSize(); }
  int GetBufferElements() const { return fInputBuffer.GetNumElements(); }
  int GetBufferSize() const { return fEvents.size(); }
  int GetEventsAdded() const { return fEventsAdded; }

  /// Convienience method
  std::vector<RIDS::PMTHit> GetHitData( RIDS::EDataSource source ) const;

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
  RAT::DS::Run* fRun; /// < The current run information
  int fEventsAdded; /// < Count of added events 

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

inline RAT::DS::Run&
DataStore::GetRun() const
{
  return *fRun;
}

inline const RIDS::Event&
DataStore::GetCurrentEvent() const
{
  return *fEvent;
}

inline bool
DataStore::HasChanged() const
{
  return fChanged;
}

} //::Viewer

#endif
