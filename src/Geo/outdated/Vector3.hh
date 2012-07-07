////////////////////////////////////////////////////////////////////////
/// \class Viewer::Vector3
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     12/07/11 : Olivia Wasalski - First Revision, new file. \n
///     12/07/11 : Olivia Wasalski - Refactored, renamed, changed inheritance tree. \n
///     08/08/11 : P.Jones - Added unit vector method.\n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Vector3__
#define __Viewer_Vector3__

#include <Viewer/Serializable.hh>
#include <Viewer/Vertex.hh>
class TVector3;

namespace Viewer
{
    class ConfigurationTable;

class Vector3 : public Serializable
{
public:

    Vector3( double x = 0.0, double y = 0.0, double z = 0.0 );
    Vector3( const TVector3& v );
    Vector3( const Vertex::Data& data );
    void SetXYZ( double x = 0.0, double y = 0.0, double z = 0.0 );
    void Render() const;
    void Load( const ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

  Vector3 operator+( const Vector3& rhs ) const;
  Vector3 operator-( const Vector3& rhs ) const;
  Vector3 operator*( const double rhs ) const;
  Vector3 operator/( const double rhs ) const;
  /// Return the unit vector
  Vector3 Unit() const;
  double Mag() const;

    double x, y, z;

}; // class Vector3


} // ::Viewer

#endif // __Viewer_Vector3
