////////////////////////////////////////////////////////////////////////
/// \class VBO
///
/// \brief  Manages the OpenGL code needed to store, create, bind and render
///         vertex buffer objects on the GPU.
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     01/05/12 : O.Wasalski - First Revision, new file. \n
///
/// \detail  Creates the vertex and index arrays needed. Binds the data to
///          the GPU side memory, and uses this bound data to render. 
///          10 times performance gain over using vertex arrays, and 100s
///          time perfomrance gain over using immediate mode rendering.
///          Should always be used to store and render large amounts of
///          3D data. Creates dependence on OpenGL > version 1.5 (2002?) . \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_VBO__
#define __Viewer_VBO__

#include <vector>
#include <SFML/OpenGL.hpp>
#include <Viewer/Vertex.hh>
#include <Viewer/Serializable.hh>

namespace Viewer {
    class ConfigurationTable;

class VBO : public Serializable {
public:
    VBO();
    void Bind();
    void AddVertex( const Vertex& v );
    void AddIndex( const unsigned short i );
    void Render( GLenum mode ) const;
    void Clear();

    void Load( const ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

    std::vector<struct Vertex::Data> fVertices;
    std::vector<unsigned short> fIndices;

    GLuint fVertexVBOID;
    GLuint fIndexVBOID;
    
};

} // namespace Viewer

#endif
