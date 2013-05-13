////////////////////////////////////////////////////////////////////////
/// \class DataSelector
///
/// \brief   Holds all the available current data.
///
/// \author  Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     28/03/13 : P.Jones - New file. First Revision. \n
///
/// \detail  This class selects events from the global data store and 
///          keeps the analysis script up to date.
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_DataSelector__
#define __Viewer_DataSelector__

#include <vector>
#include <string>

#include <Viewer/AnalysisScript.hh>
#include <Viewer/EventSelectionScript.hh>
//#include <Viewer/ChannelSelectionScript.hh>

namespace Viewer
{
namespace RIDS
{
  class Event;
  class ChannelList;
  class FibreList;
  class Channel;
}

class DataSelector
{
public:
  /// Singleton class instance
  static DataSelector& GetInstance();
  /// Initialise the DataSelector, post semaphore
  void Initialise();
  /// Destory the DataSelector
  virtual ~DataSelector();

  /// Return true if event has changed since last reset
  bool EventChanged() const { return fEventChanged; }
  /// Return true if the run has changed since last reset
  bool RunChanged() const { return fRunChanged; }
  /// Reset the changed markers
  void Reset() { fEventChanged = false; fRunChanged = false; }

  /// Move through the events
  void Move( int steps );
  /// Select the latest applicable event
  void Latest();
  /// Select the event with the given gtid
  void MoveToID( int gtid );

  /// Get the current Event
  const RIDS::Event& GetEvent() const;
  /// Get the current channel data
  const std::vector<RIDS::Channel>& GetData( int source, int type ) const;
  /// Get the type names
  const std::vector<std::string> GetTypeNames( int source ) const;
  /// Get the current ChannelList
  const RIDS::ChannelList& GetChannelList() const { return *fChannelList; }
  /// Get the current FibreList
  const RIDS::FibreList& GetFibreList() const { return *fFibreList; }

  /// Activate the analysis script
  void SetAnalyse( bool analyse ) { fAnalyse = analyse; }
  /// Set the analysis script
  void SetAnalysisScript( const std::string& script );
  /// Activate the event selection script
  void SetSelect( bool select ) { fSelect = select; }
  /// Set the event selection script
  void SetEventSelectionScript( const std::string& script );
  /// Set the event selection script input
  void SetEventSelectionInput( const std::string& input ) { fEventSelectionScript.SetInput( input ); }

private:
  AnalysisScript fAnalysisScript; /// < The analysis script
  EventSelectionScript fEventSelectionScript; /// < The event selection script
  //ChannelSelectionScript fChannelSelectionScript; /// < The channel selection script
  RIDS::Event* fEvent; /// < The currently selected event
  RIDS::ChannelList* fChannelList; /// < The channel list for fEvent
  RIDS::FibreList* fFibreList; /// < The fibre list for fEvent
  bool fSelect; /// < True if the event selection script is active
  bool fAnalyse; /// < True if the analysis script is active
  bool fEventChanged; /// < True if the event has changed since reset
  bool fRunChanged; /// < True if the run has changed since reset

  /// Prevent usage of methods below
  DataSelector();
  DataSelector( DataSelector& );
  void operator=( DataSelector& );
};

inline DataSelector&
DataSelector::GetInstance()
{
  static DataSelector eventData;
  return eventData;
}

} //::Viewer

#endif
