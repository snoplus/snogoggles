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
#include <Viewer/Serializable.hh>
#include <vector>

namespace Viewer
{
    class ConfigurationTable;

class Polygon : public Serializable
{
public:

    Polygon() { }
    Polygon( std::vector< Vector3> vertices ) 
        : fVertices( vertices ) { }

    inline void AddVertex( const Vector3& vertex );
    inline const int GetNoVertices() const;
    inline const Vector3 GetVertex( const int i ) const;

    void Render() const;

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

private:

    std::vector< Vector3 > fVertices;

}; // class Polygon

////////////////////////////////////////////////////////////////////////
// inline methods
////////////////////////////////////////////////////////////////////////

void Polygon::AddVertex( const Vector3& vertex ) 
{ 
    fVertices.push_back( vertex ); 
}

const int Polygon::GetNoVertices() const 
{ 
    return fVertices.size(); 
}

const Vector3 Polygon::GetVertex( const int i ) const 
{
    return fVertices.at(i); 
}

} // ::Viewer

#endif // __Viewer_Polygon
