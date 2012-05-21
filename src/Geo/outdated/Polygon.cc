#include <sstream>

#include <SFML/OpenGL.hpp>

#include <Viewer/ConfigurationTable.hh>
#include <Viewer/SerializableFactory.hh>
#include <Viewer/Polygon.hh>

namespace Viewer {

void Polygon::Render() const
{
    glBegin( GL_POLYGON );

    for( int v = 0; v < fVertices.size(); v++ )
        fVertices.at(v).Render();

    glEnd();
}

void Polygon::Load( ConfigurationTable* configTable )
{
    std::vector< Vector3 > vertices;
    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string name = "vertex" + stream.str();
        try { vertices.push_back( SerializableFactory::GetInstance()->New< Vector3 >( configTable, name ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    fVertices = vertices;
}

void Polygon::Save( ConfigurationTable* configTable ) const
{
    for( int i = 0; i < fVertices.size(); i++ )
    {
        std::stringstream stream; stream << i;
        std::string name = "vertex" + stream.str();
        fVertices.at(i).SaveToParentTable( configTable, name );
    }
}

}; // namespace Viewer
