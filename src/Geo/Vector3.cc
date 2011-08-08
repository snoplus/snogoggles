#include <TVector3.h>

#include <cmath>
using namespace std;

#include <SFML/OpenGL.hpp>

#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Vector3.hh>

namespace Viewer {

Vector3::Vector3( double x, double y, double z )
{
    SetXYZ( x, y, z );
}

Vector3::Vector3( const TVector3& v )
{
    SetXYZ( v.x(), v.y(), v.z() );
}

void Vector3::SetXYZ( double x, double y, double z )
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::Render() const
{
    glVertex3f( static_cast< float >( x ), 
                static_cast< float >( y ), 
                static_cast< float >( z ) 
    );
}

void Vector3::Load( ConfigurationTable* configTable )
{
    double x = configTable->GetD( "x" );
    double y = configTable->GetD( "y" );
    double z = configTable->GetD( "z" );
    SetXYZ( x, y, z );
}

void Vector3::Save( ConfigurationTable* configTable ) const
{
    configTable->SetD( "x", x );
    configTable->SetD( "y", y );
    configTable->SetD( "z", z );
}

Vector3
Vector3::operator+( const Vector3& rhs ) const
{
  return Vector3( rhs.x + x, rhs.y + y, rhs.z + z );
}

Vector3
Vector3::operator-( const Vector3& rhs ) const
{
 return Vector3( x - rhs.x, y - rhs.y, z - rhs.z );
}

Vector3
Vector3::operator*( const double rhs ) const
{
  return Vector3( x * rhs, y * rhs, z * rhs );
}

Vector3
Vector3::operator/( const double rhs ) const
{
  return Vector3( x / rhs, y / rhs, z / rhs );
}

Vector3 
Vector3::Unit() const
{
  double mag = Mag();
  return Vector3( x / mag, y / mag, z / mag );
}

double
Vector3::Mag() const
{
  return sqrt( x*x + y*y + z*z );
}

}; // namespace Viewer
