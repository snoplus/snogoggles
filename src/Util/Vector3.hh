////////////////////////////////////////////////////////////////////////
/// \class Viewer::Vector3
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

#ifndef __Viewer_Vector3__
#define __Viewer_Vector3__

#include <SFML/OpenGL.hpp>
#include <TVector3.h>

namespace Viewer
{

class Vector3 : public TVector3
{
public:

    Vector3( double x = 0.0, double y = 0.0, double z = 0.0 )
        : TVector3( x, y, z ) { }

    inline void RenderOpenGL();

    static inline std::string Tag() { return "vertex"; }
    static inline std::string XTag() { return "x"; }
    static inline std::string YTag() { return "y"; }
    static inline std::string ZTag() { return "z"; }

}; // class Vector3

void Vector3::RenderOpenGL()
{
    glVertex3f( (float) x(), (float) y(), (float) z() );
}

} // ::Viewer

#endif // __Viewer_Vector3
