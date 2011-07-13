////////////////////////////////////////////////////////////////////////
/// \class Viewer::Polyhedron
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     13/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Polyhedron__
#define __Viewer_Polyhedron__

#include <Viewer/Polygon.hh>
#include <Viewer/Colour.hh>
#include <SFML/OpenGL.hpp>
#include <vector>

namespace Viewer
{

class Polyhedron
{
public:

    Polyhedron( std::vector< Polygon > polygons, const Colour& colour )
    { fPolygons = polygons;     fColour = colour; }

    inline void RenderOpenGL();

    static inline std::string ColourTag() { return "colour"; }

    std::vector< Polygon > fPolygons;

    Colour fColour;

}; // class Polyhedron

void Polyhedron::RenderOpenGL()
{
    glPushAttrib( GL_COLOR );
    fColour.SetOpenGL();

    for( int i = 0; i < fPolygons.size(); i++ )
        fPolygons.at(i).RenderOpenGL();

    glPopAttrib( );
}

} // ::Viewer

#endif // __Viewer_Polyhedron
