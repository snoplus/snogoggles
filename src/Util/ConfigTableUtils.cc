#include <Viewer/ConfigTableUtils.hh>

#include <TVector3.h>
#include <string>

namespace Viewer {

const std::string ConfigTableUtils::TRUE_TAG = "TRUE";
const std::string ConfigTableUtils::FALSE_TAG = "FALSE";

void ConfigTableUtils::SetBoolean( ConfigurationTable* configTable, const std::string& name, bool value )
{
    if( value == true ) configTable->SetS( name, TRUE_TAG );
    else configTable->SetS( name, FALSE_TAG );
}

bool ConfigTableUtils::GetBoolean( const ConfigurationTable* configTable, const std::string& name )
{
    std::string tag = configTable->GetS( name );
    if( tag == TRUE_TAG ) return true;
    else if ( tag == FALSE_TAG ) return false;
}

void ConfigTableUtils::GetISafe( const ConfigurationTable* configTable, const std::string& name, int& value )
{
    try { value = configTable->GetI( name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetDSafe( const ConfigurationTable* configTable, const std::string& name, double& value )
{
    try { value = configTable->GetD( name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetSSafe( const ConfigurationTable* configTable, const std::string& name, std::string& value )
{
    try { value = configTable->GetS( name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetBooleanSafe( const ConfigurationTable* configTable, const std::string& name, bool& value )
{
    try { value = GetBoolean( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

}; // namespace Viewer

