#include <Viewer/ConfigTableUtils.hh>

#include <TVector3.h>
#include <string>

namespace Viewer {

const std::string ConfigTableUtils::TRUE_TAG = "TRUE";
const std::string ConfigTableUtils::FALSE_TAG = "FALSE";

const std::string ConfigTableUtils::VECTOR3_X = "x";
const std::string ConfigTableUtils::VECTOR3_Y = "y";
const std::string ConfigTableUtils::VECTOR3_Z = "z";

const std::string ConfigTableUtils::COLOUR_R = "r";
const std::string ConfigTableUtils::COLOUR_G = "g";
const std::string ConfigTableUtils::COLOUR_B = "b";
const std::string ConfigTableUtils::COLOUR_A = "a";

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

void ConfigTableUtils::SetColour( ConfigurationTable* configTable, const std::string& name, Colour value )
{
    ConfigurationTable* colourTable = configTable->NewTable( name );
    colourTable->SetI( COLOUR_R, value.r );
    colourTable->SetI( COLOUR_G, value.g );
    colourTable->SetI( COLOUR_B, value.b );
    colourTable->SetI( COLOUR_A, value.a );
}

Colour ConfigTableUtils::GetColour( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* colourTable = configTable->GetTable( name );
    int r = colourTable->GetI( COLOUR_R );
    int g = colourTable->GetI( COLOUR_G );
    int b = colourTable->GetI( COLOUR_B );
    int a = colourTable->GetI( COLOUR_A );
    return Colour( r, g, b, a );
}

void ConfigTableUtils::SetVector3( ConfigurationTable* configTable, const std::string& name, const Vector3& value )
{
    ConfigurationTable* vectorTable = configTable->NewTable( name );

    vectorTable->SetD( VECTOR3_X, value.x() );
    vectorTable->SetD( VECTOR3_Y, value.y() );
    vectorTable->SetD( VECTOR3_Z, value.z() );
}

Vector3 ConfigTableUtils::GetVector3( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* vectorTable = configTable->GetTable( name );

    double x = vectorTable->GetD( VECTOR3_X );
    double y = vectorTable->GetD( VECTOR3_Y );
    double z = vectorTable->GetD( VECTOR3_Z );

    return Vector3( x, y, z );
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

void ConfigTableUtils::GetVector3Safe( ConfigurationTable* configTable, const std::string& name, Vector3& value )
{
    try { value = GetVector3( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

};

