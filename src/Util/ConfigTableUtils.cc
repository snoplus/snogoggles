#include <Viewer/ConfigTableUtils.hh>

#include <TVector3.h>
#include <string>

namespace Viewer {

const std::string ConfigTableUtils::TRUE_TAG = "TRUE";
const std::string ConfigTableUtils::FALSE_TAG = "FALSE";

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

void ConfigTableUtils::SetBoolean( ConfigurationTable* configTable, const std::string& name, bool value )
{
    if( value == true ) configTable->SetS( name, TRUE_TAG );
    else configTable->SetS( name, FALSE_TAG );
}

bool ConfigTableUtils::GetBoolean( ConfigurationTable* configTable, const std::string& name )
{
    std::string tag = configTable->GetS( name );
    if( tag == TRUE_TAG ) return true;
    else if ( tag == FALSE_TAG ) return false;
}

void ConfigTableUtils::GetISafe( ConfigurationTable* configTable, const std::string& name, int& value )
{
    try { value = configTable->GetI( name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetDSafe( ConfigurationTable* configTable, const std::string& name, double& value )
{
    try { value = configTable->GetD( name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetSSafe( ConfigurationTable* configTable, const std::string& name, std::string& value )
{
    try { value = configTable->GetS( name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetBooleanSafe( ConfigurationTable* configTable, const std::string& name, bool& value )
{
    try { value = GetBoolean( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetTVector3Safe( ConfigurationTable* configTable, const std::string& name, TVector3& value )
{
    try { value = GetTVector3( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

};

