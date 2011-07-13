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

void ConfigTableUtils::SetColour( ConfigurationTable* configTable, const std::string& name, Colour value )
{
    ConfigurationTable* colourTable = configTable->NewTable( name );
    colourTable->SetI( "r", value.r );
    colourTable->SetI( "g", value.g );
    colourTable->SetI( "b", value.b );
    colourTable->SetI( "a", value.a );
}

Colour ConfigTableUtils::GetColour( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* colourTable = configTable->GetTable( name );
    int r = colourTable->GetI( "r" );
    int g = colourTable->GetI( "g" );
    int b = colourTable->GetI( "b" );
    return Colour( r, g, b );
}

void ConfigTableUtils::SetPolyhedron( ConfigurationTable* configTable, const Polyhedron& value )
{
    SetColour( configTable, Polyhedron::ColourTag(), value.fColour );

    for( int i = 0; i < value.fPolygons.size(); i++ )
    {
        std::stringstream stream;
        stream << i;
        std::string polygonName = Polygon::Tag() + stream.str();
        SetPolygon( configTable, polygonName, value.fPolygons.at(i) );
    }
}

Polyhedron ConfigTableUtils::GetPolyhedron( ConfigurationTable* configTable )
{
    int i = 0;
    std::vector< Polygon > polygons;

    while( true )
    {
        std::stringstream stream;
        stream << i;
        std::string polygonName = Polygon::Tag() + stream.str();
        try { polygons.push_back( GetPolygon( configTable, polygonName ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return Polyhedron( polygons, GetColour( configTable, Polyhedron::ColourTag() ) );
}

void ConfigTableUtils::SetPolygon( ConfigurationTable* configTable, const std::string& name, const Polygon& value )
{
    ConfigurationTable* polygonTable = configTable->NewTable( name );

    for( int i = 0; i < value.fVertices.size(); i++ )
    {
        std::stringstream stream;
        stream << i;
        std::string vectorName = Vector3::Tag() + stream.str();
        SetVector3( polygonTable, vectorName, value.fVertices.at(i) );
    }
}

Polygon ConfigTableUtils::GetPolygon( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* polygonTable = configTable->GetTable( name );

    int i = 0;
    std::vector< Vector3 > vertices;

    while( true )
    {
        std::stringstream stream;
        stream << i;
        std::string vectorName = Vector3::Tag() + stream.str();
        try { vertices.push_back( GetVector3( polygonTable, vectorName ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return Polygon( vertices );
}

void ConfigTableUtils::SetVector3( ConfigurationTable* configTable, const std::string& name, const Vector3& value )
{
    ConfigurationTable* vectorTable = configTable->NewTable( name );

    vectorTable->SetD( Vector3::XTag(), value.x() );
    vectorTable->SetD( Vector3::YTag(), value.y() );
    vectorTable->SetD( Vector3::ZTag(), value.z() );
}

Vector3 ConfigTableUtils::GetVector3( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* vectorTable = configTable->GetTable( name );

    double x = vectorTable->GetD( Vector3::XTag() );
    double y = vectorTable->GetD( Vector3::YTag() );
    double z = vectorTable->GetD( Vector3::ZTag() );

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

void ConfigTableUtils::GetTVector3Safe( ConfigurationTable* configTable, const std::string& name, TVector3& value )
{
    try { value = GetTVector3( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void ConfigTableUtils::GetVector3Safe( ConfigurationTable* configTable, const std::string& name, Vector3& value )
{
    try { value = GetVector3( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

};

