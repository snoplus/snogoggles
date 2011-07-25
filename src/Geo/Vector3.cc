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

}; // namespace Viewer
