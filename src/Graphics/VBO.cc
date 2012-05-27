#define GL_GLEXT_PROTOTYPES

#include <sstream>
#include <string>
#include <iostream>

#include <TVector3.h>

#include <Viewer/Colour.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/VBO.hh>

namespace Viewer {

VBO::VBO()
{
    glGenBuffers( 1, &fVertexVBOID );
    glGenBuffers( 1, &fIndexVBOID );
}

void VBO::Bind()
{
    glBindBuffer( GL_ARRAY_BUFFER, fVertexVBOID );
    glBufferData( GL_ARRAY_BUFFER, fVertices.size()*sizeof(struct Vertex::Data), &fVertices[0], GL_DYNAMIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, fIndexVBOID );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, fIndices.size()*sizeof(unsigned short), &fIndices[0], GL_DYNAMIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void VBO::AddVertex( const Vertex& v )
{
    fVertices.push_back(v.fData);
}

void VBO::AddIndex( const unsigned short i )
{
    fIndices.push_back(i);
}

void VBO::Render( GLenum mode ) const
{
    glBindBuffer( GL_ARRAY_BUFFER, fVertexVBOID );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, fIndexVBOID );

    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    glVertexPointer( 3, GL_FLOAT, sizeof( struct Vertex::Data ), 0 );
    glColorPointer( 4, GL_FLOAT, sizeof( struct Vertex::Data ), (const GLvoid*) (3*sizeof(float)));

    glDrawElements( mode, fIndices.size(), GL_UNSIGNED_SHORT, 0 );
    
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_COLOR_ARRAY );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void VBO::Clear()
{
    fVertices.clear();
    fIndices.clear();
}

void VBO::Load( const ConfigurationTable* configTable )
{
    Clear();

    Colour colour;
    colour.Load( configTable->GetTable("colour") );
    
    const ConfigurationTable* vertices = configTable->GetTable("vertices");
    for( int i = 0; i < configTable->GetI("num_vertices"); i++ )
    {
        std::stringstream ss; ss << i;
        const ConfigurationTable* v = vertices->GetTable( "vertex" + ss.str() );
        AddVertex( Vertex (
            (86/89.0)*TVector3( v->GetD("x"), v->GetD("y"), v->GetD("z") ),
            colour
        ) );
    }

    const ConfigurationTable* indices = configTable->GetTable("indices");
    for( int i = 0; i < configTable->GetI("num_indices"); i++ )
    {
        std::stringstream ss; ss << i;
        AddIndex( (unsigned short) indices->GetI( "i" + ss.str() ) ); 
    }
    
    Bind();

}

void VBO::Save( ConfigurationTable* configTable ) const
{
    // TODO:
}


}; // namespace Viewer
