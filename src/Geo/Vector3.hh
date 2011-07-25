////////////////////////////////////////////////////////////////////////
/// \class Viewer::Vector3
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     12/07/11 : Olivia Wasalski - First Revision, new file. \n
///     12/07/11 : Olivia Wasalski - Refactored, renamed, changed inheritance tree. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Vector3__
#define __Viewer_Vector3__

#include <TVector3.h>
#include <SFML/OpenGL.hpp>
#include <Viewer/Serializable.hh>

namespace Viewer
{
    class ConfigurationTable;

class Vector3 : public Serializable
{
public:

    Vector3( double x = 0.0, double y = 0.0, double z = 0.0 );
    Vector3( const TVector3& v );
    void SetXYZ( double x = 0.0, double y = 0.0, double z = 0.0 );

    inline void Render() const;

    void Load( ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

    double x, y, z;

}; // class Vector3

void Vector3::Render() const
{
    glVertex3f( static_cast< float >( x ), 
                static_cast< float >( y ), 
                static_cast< float >( z ) 
    );
}

} // ::Viewer

#endif // __Viewer_Vector3
