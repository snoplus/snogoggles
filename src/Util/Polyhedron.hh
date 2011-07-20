////////////////////////////////////////////////////////////////////////
/// \class Viewer::Polyhedron
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     13/07/11 : Olivia Wasalski - First Revision, new file. \n
///     19/07/11 : Olivia Wasalski - Removed colour. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Polyhedron__
#define __Viewer_Polyhedron__

#include <Viewer/Polygon.hh>
#include <vector>

namespace Viewer
{

class Polyhedron
{
public:

    Polyhedron() { }

    Polyhedron( std::vector< Polygon > polygons )
    { fPolygons = polygons; }

    inline void RenderOpenGL();

    std::vector< Polygon > fPolygons;

    Colour fColour;

}; // class Polyhedron

void Polyhedron::RenderOpenGL()
{
    for( int i = 0; i < fPolygons.size(); i++ )
        fPolygons.at(i).RenderOpenGL();
}

} // ::Viewer

#endif // __Viewer_Polyhedron
