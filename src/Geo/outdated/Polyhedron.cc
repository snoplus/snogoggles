#include <sstream>

#include <Viewer/ConfigurationTable.hh>
#include <Viewer/SerializableFactory.hh>
#include <Viewer/Polyhedron.hh>

namespace Viewer {

void Polyhedron::Load( const ConfigurationTable* configTable )
{
    std::vector< Polygon > polygons;
    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string name = "polygon" + stream.str();
        try{ polygons.push_back( SerializableFactory::GetInstance()->New< Polygon >( configTable, name ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }
    fPolygons = polygons;
}

void Polyhedron::Save( ConfigurationTable* configTable ) const
{
    for( int i = 0; i < fPolygons.size(); i++ )
    {
        std::stringstream stream; stream << i;
        std::string name = "polygon" + stream.str();
        fPolygons.at(i).SaveToParentTable( configTable, name );
    }
}

}; // namespace Viewer
