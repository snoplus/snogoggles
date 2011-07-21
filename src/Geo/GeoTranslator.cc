#include <sstream>

#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/StringUtils.hh>
#include <Viewer/World.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/GeoTranslator.hh>

namespace Viewer {

const std::string GeoTranslator::VOLUME = "volume";
const std::string GeoTranslator::VOLUME_NAME = "name";
const std::string GeoTranslator::VOLUME_TRANSLATION = "translation";
const std::string GeoTranslator::VOLUME_ROTATION_AXIS = "rotationAxis";
const std::string GeoTranslator::VOLUME_ROTATION_ANGLE = "rotationAngle";

const std::string GeoTranslator::POLYHEDRON = "polyhedron";
const std::string GeoTranslator::POLYGON = "polygon";
const std::string GeoTranslator::VERTEX = "vertex";

const std::string GeoTranslator::VIS_ATTRIBUTES = "visAttributes";
const std::string GeoTranslator::VIS_ATTRIBUTES_NAMES = "names";
const std::string GeoTranslator::VIS_ATTRIBUTES_COLOUR = "colour";
const std::string GeoTranslator::VIS_ATTRIBUTES_VISIBLE = "visible";

void 
GeoTranslator::SetWorld( ConfigurationTable* configTable, World* value )
{
    std::map< std::string, VisAttributes* > named = value->fVisAttributeMap;
    SetVisAttributeMap( configTable, VIS_ATTRIBUTES, named );
    SetVolume( configTable, VOLUME, value->fVolume );
}

World* 
GeoTranslator::GetWorld( ConfigurationTable* configTable )
{
    Volume vol = GetVolume( configTable, VOLUME );
    std::map< std::string, VisAttributes* > vis = GetVisAttributeMap( configTable, VIS_ATTRIBUTES );
    return new World( vol, vis );
}

void 
GeoTranslator::SetVisAttributeMap( ConfigurationTable* configTable, const std::string& name, std::map< std::string, VisAttributes* >& value )
{
    ConfigurationTable* visAttrTable = configTable->NewTable( name );
    std::string names = "";

    std::map< std::string, VisAttributes* >::iterator itr;
    for( itr = value.begin(); itr != value.end(); itr++ )
    {
        names += itr->first; names += " ";
        SetVisAttributes( visAttrTable, itr->first, itr->second );
    }

    visAttrTable->SetS( VIS_ATTRIBUTES_NAMES, names );
}

std::map< std::string, VisAttributes* > 
GeoTranslator::GetVisAttributeMap( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* visAttrTable = configTable->GetTable( name );

    std::map< std::string, VisAttributes* > visAttributeMap;
    std::vector< std::string > names;
    StringUtils::SplitString( visAttrTable->GetS( VIS_ATTRIBUTES_NAMES ), " ", names );

    for( int i = 0; i < names.size(); i++ )
        visAttributeMap[ names.at(i) ] = GetVisAttributes( visAttrTable, names.at(i) );

    return visAttributeMap;
}

void 
GeoTranslator::SetVisAttributes( ConfigurationTable* configTable, const std::string& name, const VisAttributes* value )
{
    ConfigurationTable* attrTable = configTable->NewTable( name );
    ConfigTableUtils::SetColour( attrTable, VIS_ATTRIBUTES_COLOUR, value->GetColour() );
    ConfigTableUtils::SetBoolean( attrTable, VIS_ATTRIBUTES_VISIBLE, value->IsVisible() );
}

VisAttributes* 
GeoTranslator::GetVisAttributes( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* attrTable = configTable->GetTable( name );
    return new VisAttributes(
        ConfigTableUtils::GetColour( attrTable, VIS_ATTRIBUTES_COLOUR ),
        ConfigTableUtils::GetBoolean( attrTable, VIS_ATTRIBUTES_VISIBLE )
    );
}

void 
GeoTranslator::SetVolume( ConfigurationTable* configTable, const std::string& name, Volume& value )
{
    ConfigurationTable* volTable = configTable->NewTable( name );

    volTable->SetS( VOLUME_NAME, value.GetName() );
    ConfigTableUtils::SetVector3( volTable, VOLUME_TRANSLATION, value.GetTranslation() );
    ConfigTableUtils::SetVector3( volTable, VOLUME_ROTATION_AXIS, value.GetRotationAxis() );
    volTable->SetD( VOLUME_ROTATION_ANGLE, value.GetRotationAngle() );
    SetPolyhedron( volTable, POLYHEDRON, *(value.GetPolyhedron()) );

    for( int i = 0; i < value.GetNoDaughters(); i++ )
    {
        std::stringstream stream;
        stream << i;
        std::string volumeName = VOLUME + stream.str();
        SetVolume( volTable, volumeName, *(value.GetDaughter(i)) );
    }
}

Volume 
GeoTranslator::GetVolume( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* volTable = configTable->GetTable( name );

    Volume volume(
        volTable->GetS( VOLUME_NAME ),
        ConfigTableUtils::GetVector3( volTable, VOLUME_TRANSLATION ),
        ConfigTableUtils::GetVector3( volTable, VOLUME_ROTATION_AXIS ),
        volTable->GetD( VOLUME_ROTATION_ANGLE ),
        GetPolyhedron( volTable, POLYHEDRON )
    );

    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string volumeName = VOLUME + stream.str();
        try 
        { 
            Volume daughter = GetVolume( volTable, volumeName );
            volume.AddDaughter( daughter ); 
        }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return volume;
}

void 
GeoTranslator::SetPolyhedron( ConfigurationTable* configTable, const std::string& name, const Polyhedron& value )
{
    ConfigurationTable* polyhedronTable = configTable->NewTable( name );

    for( int i = 0; i < value.GetNoPolygons(); i++ )
    {
        std::stringstream stream; stream << i;
        std::string polygonName = POLYGON + stream.str();
        SetPolygon( polyhedronTable, polygonName, value.GetPolygon(i) );
    }
}

Polyhedron 
GeoTranslator::GetPolyhedron( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* polyhedronTable = configTable->GetTable( name );
    Polyhedron polyhedron;

    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string polygonName = POLYGON + stream.str();
        try { polyhedron.AddPolygon( GetPolygon( polyhedronTable, polygonName ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return polyhedron;
}

void 
GeoTranslator::SetPolygon( ConfigurationTable* configTable, const std::string& name, const Polygon& value )
{
    ConfigurationTable* polygonTable = configTable->NewTable( name );

    for( int i = 0; i < value.GetNoVertices(); i++ )
    {
        std::stringstream stream; stream << i;
        std::string vertexName = VERTEX + stream.str();
        ConfigTableUtils::SetVector3( polygonTable, vertexName, value.GetVertex(i) );
    }
}

Polygon 
GeoTranslator::GetPolygon( ConfigurationTable* configTable, const std::string& name )
{
    ConfigurationTable* polygonTable = configTable->GetTable( name );
    Polygon polygon;

    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string vertexName = VERTEX + stream.str();
        try { polygon.AddVertex( ConfigTableUtils::GetVector3( polygonTable, vertexName ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    return polygon;
}


}; // namespace Viewer
