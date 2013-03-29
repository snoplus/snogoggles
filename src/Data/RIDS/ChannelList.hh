////////////////////////////////////////////////////////////////////
/// \class ChannelList
///
/// \brief ChannelList data structure
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 22/03/13 : P.Jones - New RIDS Refactor. \n
///
/// \detail This holds the information about what channels exist, where
///         they are excetera.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_ChannelList__
#define __Viewer_RIDS_ChannelList__

#include <SFML/System/Vector3.hpp>

#include <vector>

namespace Viewer
{
namespace RIDS
{

class ChannelList
{
public:
  /// Initialise the database with the runID
  void Initialise( int runID );

  /// Return the number of channels
  int GetChannelCount() const { return fPositions.size(); }
  /// Return the position for channel id
  const sf::Vector3<double> GetPosition( int id ) const { return fPositions[id]; }
private:
  std::vector< sf::Vector3<double> > fPositions; /// < PMT Positions

  int fRunID; /// < Channel list should reinitialise if run changes
};

} // namespace RIDS

} // namespace Viewer

#endif
