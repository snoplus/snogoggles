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
    int a = colourTable->GetI( "a" );
    return Colour( r, g, b, a );
}

void ConfigTableUtils::SetVolume( ConfigurationTable* configTable, const std::string& name, const Volume* value )
{
    ConfigurationTable* volumeTable = configTable->NewTable( Volume::Tag() );
    SetVolume( volumeTable, value );
}

void ConfigTableUtils::SetVolume( ConfigurationTable* configTable, const Volume* value )
{
    configTable->SetS( Volume::NAME_TAG, value->GetName() );
    SetBoolean( configTable, Volume::VISIBLE_TAG, value->IsVisible() );
    SetColour( configTable, Volume::COLOUR_TAG, value->GetColour() );
    SetVector3( configTable, Volume::TRANSLATION_TAG, value->GetTranslation() );
    SetVector3( configTable, Volume::ROTATION_AXIS_TAG, value->GetRotationAxis() );
    configTable->SetD( Volume::ROTATION_ANGLE_TAG, value->GetRotationAngle() );
    SetPolyhedron( configTable, Volume::POLYHEDRON_TAG, *(value->GetPolyhedron()) );

    for( int i = 0; i < value->GetNoDaughters(); i++ )
    {
        std::stringstream stream;
        stream << i;
        std::string volumeName = Volume::Tag() + stream.str();
        SetVolume( configTable, volumeName, value->GetDaughter(i) );
    }
}

Volume* ConfigTableUtils::GetVolume( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* volumeTable = configTable->GetTable( name );
    return GetVolume( volumeTable );
}

Volume* ConfigTableUtils::GetVolume( ConfigurationTable* configTable )
{
    std::vector< Volume* > volumes;
    int i = 0;
    while( true )
    {
        std::stringstream stream;
        stream << i;
        std::string volumeName = Volume::Tag() + stream.str();
        try { volumes.push_back( GetVolume( configTable, volumeName ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return new Volume(
        configTable->GetS( Volume::NAME_TAG ),
        GetBoolean( configTable, Volume::VISIBLE_TAG ),
        GetColour( configTable, Volume::COLOUR_TAG ),
        GetVector3( configTable, Volume::TRANSLATION_TAG ),
        GetVector3( configTable, Volume::ROTATION_AXIS_TAG ),
        configTable->GetD( Volume::ROTATION_ANGLE_TAG ),
        volumes,
        GetPolyhedron( configTable, Volume::POLYHEDRON_TAG )
    );
}

void ConfigTableUtils::SetPolyhedron( ConfigurationTable* configTable, const std::string& name, const Polyhedron& value )
{
    ConfigurationTable* polyhedronTable = configTable->NewTable( name );

    for( int i = 0; i < value.fPolygons.size(); i++ )
    {
        std::stringstream stream;
        stream << i;
        std::string polygonName = Polygon::Tag() + stream.str();
        SetPolygon( polyhedronTable, polygonName, value.fPolygons.at(i) );
    }
}

Polyhedron ConfigTableUtils::GetPolyhedron( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* polyhedronTable = configTable->GetTable( name );
    int i = 0;
    std::vector< Polygon > polygons;

    while( true )
    {
        std::stringstream stream;
        stream << i;
        std::string polygonName = Polygon::Tag() + stream.str();
        try { polygons.push_back( GetPolygon( polyhedronTable, polygonName ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return Polyhedron( polygons );
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

void ConfigTableUtils::GetVector3Safe( ConfigurationTable* configTable, const std::string& name, Vector3& value )
{
    try { value = GetVector3( configTable, name ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

};

