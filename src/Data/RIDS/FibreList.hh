////////////////////////////////////////////////////////////////////
/// \class FibreList
///
/// \brief FibreList data structure
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 15/04/13 : P.Jones - New RIDS Refactor. \n
///
/// \detail This holds the information about what fibres exist, where
///         they are excetera.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_FibreList__
#define __Viewer_RIDS_FibreList__

#include <SFML/System/Vector3.hpp>

#include <vector>

namespace Viewer
{
namespace RIDS
{

class FibreList
{
public:
  enum EType { eAMELLIE, eSMELLIE, eTELLIE };

  /// Initialise the database with the runID
  void Initialise( int runID );

  /// Return the number of fibre
  int GetFibreCount() const { return fPositions.size(); }
  /// Return the position for fibre id
  const sf::Vector3<double> GetPosition( int id ) const { return fPositions[id]; }
  /// Return the direction for fibre id
  const sf::Vector3<double> GetDirection( int id ) const { return fDirections[id]; }
  /// Return the fibre type for the fibre id
  const EType GetType( int id ) const { return fTypes[id]; }
private:
  std::vector< sf::Vector3<double> > fPositions; /// < Fibre Positions
  std::vector< sf::Vector3<double> > fDirections; /// < Fibre Directions
  std::vector< EType > fTypes; /// < Fibre type

  int fRunID; /// < Fibre list should reinitialise if run changes
};

} // namespace RIDS

} // namespace Viewer

#endif
