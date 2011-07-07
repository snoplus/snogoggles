#include <Viewer/ConfigTableUtils.hh>

#include <TVector3.h>
#include <string>

namespace Viewer {

void ConfigTableUtils::SetTVector3( ConfigurationTable* configTable, const std::string& name, const TVector3& v )
{
    configTable->SetD( name + ".X" , v.X() );
    configTable->SetD( name + ".Y" , v.Y() );
    configTable->SetD( name + ".Z" , v.Z() );
}

TVector3 ConfigTableUtils::GetTVector3( ConfigurationTable* configTable, const std::string& name )
{
    TVector3 v;
    v.SetXYZ(
        configTable->GetD( name + ".X" ),
        configTable->GetD( name + ".Y" ),
        configTable->GetD( name + ".Z" )
    );
    return v;
}

};

