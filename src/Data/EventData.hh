////////////////////////////////////////////////////////////////////////
/// \class EventData
///
/// \brief   Holds all the available current data.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     12/05/11 : P.Jones - First Revision, new file. \n
///     27/02/12 : P.Jones - Second Revision, replace old version, 
///                hopefully more stable.
///
/// \detail  Holds RAT::DS::Root events and the RAT::DS::Run data. 
///          Also has an index to the current DS event and then the 
///          current sub ev event.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_EventData__
#define __Viewer_EventData__

#include <RAT/DS/Root.hh>

#include <vector>

#include <Viewer/Mutex.hh>

namespace RAT
{
namespace DS
{
  class EV;
  class Run;
  class MC;
}
}

namespace Viewer
{

class EventData
{
public:
  static EventData& GetInstance();

  void Initialise();

  virtual ~EventData();

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

  inline RAT::DS::Run* GetRun();
  inline RAT::DS::Root* GetCurrentDS();
  inline RAT::DS::EV* GetCurrentEV();
  inline RAT::DS::MC* GetCurrentMC();

private:
  Mutex fLock; /// < The lock
  // These must be locked to read/write
  std::vector<RAT::DS::Root*> fEvents; /// < Event data array, writing will roll over and overwrite events from 0
  unsigned int fWriteIndex;  /// < Current write position
  unsigned int fDSIndex; /// < The current DS event
  // This must be locked to write
  RAT::DS::Root* fDS; /// < Copy of the currently viewed event (stops it being deleted)
  RAT::DS::Run* fRun; /// < Run tree
  // End locked vars
  unsigned int fEVIndex; /// < The current sub EV event (typically 0)
  //ScriptData* fScriptData; /// < The script data TODO

  /// Prevent usage of
  EventData();
  EventData( EventData& );
  void operator=( EventData& );
};

inline EventData&
EventData::GetInstance()
{
  static EventData eventData;
  return eventData;
}

inline RAT::DS::Run*
EventData::GetRun()
{
  return fRun;
}

inline RAT::DS::Root*
EventData::GetCurrentDS()
{
  return fDS;
}

inline RAT::DS::EV*
EventData::GetCurrentEV()
{
  return GetCurrentDS()->GetEV( fEVIndex );
}

inline RAT::DS::MC*
EventData::GetCurrentMC()
{
  return GetCurrentDS()->GetMC();
}

} //::Viewer

#endif
