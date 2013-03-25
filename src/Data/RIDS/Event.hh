////////////////////////////////////////////////////////////////////
/// \class Event
///
/// \brief Event data structure
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 20/03/13 : P.Jones - New RIDS Refactor. \n
///
/// \detail This class holds all the event relevant data to display,
///         in a generic format that accomodates ORCA, built and MC
///         data in a ROOT independent manner.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_Event__
#define __Viewer_RIDS_Event__

#include <vector>
#include <string>

#include <Viewer/RIDS/Source.hh>
#include <Viewer/RIDS/Time.hh>

namespace Viewer
{
namespace RIDS
{
  typedef std::vector< std::pair< std::string, std::vector< std::string > > > DataNames;


class Event
{
public:
  static void Initialise( const DataNames& sourceTypeStrings ) { fsDataNames = sourceTypeStrings; }
  static std::vector<std::string> GetSourceNames();
  static std::vector<std::string> GetTypeNames( int source );
  
  /// Builds the event, adds the specified number of sources each with the specified number of types
  Event();
  /// Set the source of id
  void SetSource( int id, Source& source ) { fSources[id] = source; }
  /// Set the run ID
  void SetRunID( int runID ) { fRunID = runID; }
  /// Set the sub run ID
  void SetSubRunID( int subRunID ) { fSubRunID = subRunID; }

  /// Return a reference to the source as specified by it's id
  const Source& GetSource( int id ) const { return fSources[id]; }
  /// Return a vector of channel data in this event given the source and data type
  const std::vector<Channel>& GetData( size_t source, /// < Data source index
                                       size_t type ) const; /// < Data type index
  /// Return the event's timestamp
  Time GetTime() const { return fTime; }
  /// Return the run ID
  int GetRunID() const { return fRunID; }
  /// Return the sub run ID
  int GetSubRunID() const { return fSubRunID; }
private:
  static DataNames fsDataNames; /// < Names of the sources each associated with type names

  Time fTime;
  std::vector<Source> fSources; /// < The event data organised by source
  int fRunID; /// < The run number
  int fSubRunID; /// < The sub run number
};

} // namespace RIDS

} // namespace Viewer

#endif
