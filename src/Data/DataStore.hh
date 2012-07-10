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
///
/// \detail  Holds RIDS::Event events and the RAT::DS::Run data. 
///          Also has an index to the current DS event and then the 
///          current sub ev event.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_DataStore__
#define __Viewer_DataStore__

#include <vector>

#include <Viewer/Mutex.hh>
#include <Viewer/ScriptData.hh>
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
  /// Add a ds to the structure
  bool AddDS( RAT::DS::Root* rDS );
  /// Move to the latest event
  void Latest();
  /// Move to the next event, rolls over
  void Next();
  /// Move to the previous event, rolls over
  void Prev();

  inline const RIDS::Event& GetCurrentEvent() const;
  inline RAT::DS::Run& GetRun() const;
  inline ScriptData& GetScriptData();
  inline bool HasChanged() const;
  inline void Reset();

  const int GetBufferSize();
  const int GetBufferRead();
  const int GetBufferWrite();

  /// Convienience method
  std::vector<RIDS::PMTHit> GetHitData( RIDS::EDataSource source ) const;

private:
  Mutex fLock; /// < The lock
  // LOCK(r/w): These must be locked to read/write
  std::vector<RIDS::Event*> fEvents; /// < Event data array, writing will roll over and overwrite events from 0
  unsigned int fWriteIndex;  /// < Current write event position
  unsigned int fReadIndex; /// < Current read event position
  // LOCK(w): These must be locked to write
  RIDS::Event* fEvent; /// < Copy of the currently viewed event (stops it being deleted)
  RAT::DS::Run* fRun; /// < Run tree
  // END: End locked vars
  ScriptData fScriptData; /// < The data as calculated by a python script
  bool fChanged;

  /// Prevent usage of
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

inline ScriptData&
DataStore::GetScriptData()
{
  return fScriptData;
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

inline void
DataStore::Reset()
{
  fChanged = false;
}

} //::Viewer

#endif
