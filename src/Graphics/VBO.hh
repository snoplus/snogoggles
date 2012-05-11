////////////////////////////////////////////////////////////////////////
/// \class VBO
///
/// \brief   
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     01/05/12 : O.Wasalski - First Revision, new file. \n
///
/// \detail  
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
    void Render( GLenum mode );
    void Clear();

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

    std::vector<struct Vertex::Data> fVertices;
    std::vector<unsigned short> fIndices;

    GLuint fVertexVBOID;
    GLuint fIndexVBOID;
    
};

} // namespace Viewer

#endif
