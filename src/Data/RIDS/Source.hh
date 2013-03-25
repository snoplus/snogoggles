////////////////////////////////////////////////////////////////////
/// \class Source
///
/// \brief Source data structure
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

#ifndef __Viewer_RIDS_Source__
#define __Viewer_RIDS_Source__

#include <vector>

#include <Viewer/RIDS/Type.hh>
#include <Viewer/RIDS/Channel.hh>

namespace Viewer
{
namespace RIDS
{

class Source
{
public:
  Source( size_t types ) { fTypes.resize( types ); }
  /// Return the size of the channel vector in the Type (each Type should have the same size)
  size_t GetDataSize() const;
  /// Set the type data for id
  void SetType( size_t id, Type& type ) { fTypes[id] = type; }
  /// Return the type data by type id
  const Type& GetType( size_t id ) const { return fTypes[id]; }
  /// Return the number of channels in the data
  const size_t GetCount() const { return fTypes[0].GetCount(); }
  /// Return a vector of channel data in this event given the source and data type
  const std::vector<Channel>& GetData( size_t type ) const { return fTypes[type].GetData(); }
private:
  Source();

  std::vector<Type> fTypes; /// < The source data organised by type

};

} // namespace RIDS

} // namespace Viewer

#endif
