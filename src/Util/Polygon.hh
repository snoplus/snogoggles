////////////////////////////////////////////////////////////////////////
/// \class Viewer::Polygon
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     12/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Polygon__
#define __Viewer_Polygon__

#include <Viewer/Vector3.hh>
#include <SFML/OpenGL.hpp>
#include <vector>

namespace Viewer
{

class Polygon
{
public:

    Polygon( std::vector<Vector3> vertices ) { fVertices = vertices; }

    inline void RenderOpenGL();

    static inline std::string Tag() { return "polygon"; }

    std::vector<Vector3> fVertices;

}; // class Polygon

void Polygon::RenderOpenGL()
{
    glBegin( GL_POLYGON );

    for( int v = 0; v < fVertices.size(); v++ )
        fVertices.at(v).RenderOpenGL();

    glEnd();
}

} // ::Viewer

#endif // __Viewer_Polygon
