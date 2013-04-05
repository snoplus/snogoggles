////////////////////////////////////////////////////////////////////
/// \class Vertex
///
/// \brief Vertex data structure
///
/// \author Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
/// 05/04/13 : P.Jones - New File, first revision. \n
///
/// \detail Holds a vertex
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_Vertex__
#define __Viewer_RIDS_Vertex__

#include <SFML/System/Vector3.hpp>

#include <vector>
#include <string>

namespace Viewer
{
namespace RIDS
{

class Vertex
{
public:
  /// Set the vertex name
  void SetName( const std::string& name ) { fName = name; }
  /// Set the vertex position
  void SetPosition( const sf::Vector3<double>& pos ) { fPosition = pos; }
  /// Set the vertex time
  void SetTime( const double time ) { fTime = time; }
  /// Return the vertex space coord
  sf::Vector3<double> GetPosition() const { return fPosition; }
  /// Return the vertex time coord
  double GetTime() const { return fTime; }
  /// Return the vertex name
  std::string GetName() const { return fName; }
private:
  std::string fName; /// < Vertex name (fit name or MC)
  sf::Vector3<double> fPosition; /// < Position
  double fTime; /// < Time
};

} // namespace RIDS

} // namespace Viewer

#endif
