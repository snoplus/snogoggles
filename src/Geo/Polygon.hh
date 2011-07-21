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

    Polygon() { }

    inline void AddVertex( const Vector3& vertex ) { fVertices.push_back( vertex ); }
    inline const int GetNoVertices() const { return fVertices.size(); }
    inline const Vector3 GetVertex( const int i ) const { return fVertices.at(i); }

    inline void Render() const;

    std::vector< Vector3 > fVertices;

}; // class Polygon

void Polygon::Render() const
{
    glBegin( GL_POLYGON );

    for( int v = 0; v < fVertices.size(); v++ )
        fVertices.at(v).Render();

    glEnd();
}

} // ::Viewer

#endif // __Viewer_Polygon
