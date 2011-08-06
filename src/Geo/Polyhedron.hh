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
#include <Viewer/Serializable.hh>
#include <vector>

namespace Viewer
{
    class ConfigurationTable;

class Polyhedron : public Serializable
{
public:

    Polyhedron() { }

    inline void AddPolygon( const Polygon& polygon );
    inline const int GetNoPolygons() const;
    inline const Polygon& GetPolygon( int i ) const;

    inline void Render() const;

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

private:

    std::vector< Polygon > fPolygons;

}; // class Polyhedron

////////////////////////////////////////////////////////////////////////
// inline methods
////////////////////////////////////////////////////////////////////////

void Polyhedron::AddPolygon( const Polygon& polygon )
{
    fPolygons.push_back( polygon );
}

const int Polyhedron::GetNoPolygons() const
{
    return fPolygons.size();
}

const Polygon& Polyhedron::GetPolygon( int i ) const
{
    return fPolygons.at(i);
}

void Polyhedron::Render() const
{
    for( int i = 0; i < fPolygons.size(); i++ )
        fPolygons.at(i).Render();
}

} // ::Viewer

#endif // __Viewer_Polyhedron
