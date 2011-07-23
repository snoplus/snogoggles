#include <Viewer/ConfigurationTable.hh>
#include <Viewer/Vector3.hh>

namespace Viewer {

void Vector3::Load( ConfigurationTable* configTable )
{
    double x = configTable->GetD( "x" );
    double y = configTable->GetD( "y" );
    double z = configTable->GetD( "z" );
    SetXYZ( x, y, z );
}

void Vector3::Save( ConfigurationTable* configTable ) const
{
    configTable->SetD( "x", x() );
    configTable->SetD( "y", y() );
    configTable->SetD( "z", z() );
}

}; // namespace Viewer
