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

    inline void AddPolygon( const Polygon& polygon ) { fPolygons.push_back( polygon ); }
    inline const int GetNoPolygons() const { return fPolygons.size(); }
    inline const Polygon GetPolygon( int i ) const { return fPolygons.at(i); }

    inline void Render() const;

    std::vector< Polygon > fPolygons;

}; // class Polyhedron

void Polyhedron::Render() const
{
    for( int i = 0; i < fPolygons.size(); i++ )
        fPolygons.at(i).Render();
}

} // ::Viewer

#endif // __Viewer_Polyhedron
