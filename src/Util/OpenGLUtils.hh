////////////////////////////////////////////////////////////////////////
/// \class Viewer::OpenGLUtils
///
/// \brief   Utility functions to facilitate rendering in OpenGL
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	07/07/11 : Olivia Wasalski - New File \n
///
/// \details 
///
////////////////////////////////////////////////////////////////////////
#ifndef __Viewer_OpenGLUtils__
#define __Viewer_OpenGLUtils__

#include <TVector3.h>

namespace Viewer {

class OpenGLUtils {

public:

    static void RotateGLMatrix( const TVector3& initialVector, const TVector3& finalVector );


}; // class OpenGLUtils

}; // namespace Viewer

#endif // __Viewer_OpenGLUtils__
