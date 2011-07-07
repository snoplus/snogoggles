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
#ifndef __Viewer_OpenGLUtilsUtils__
#define __Viewer_OpenGLUtilsUtils__

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

namespace Viewer {

class OpenGLUtilsUtils {

public:

    static inline void SetColour( sf::Color& colour )
    {
        glColor4f( 
            colour.r/fColourRatio,
            colour.g/fColourRatio,
            colour.b/fColourRatio,
            colour.a/fColourRatio
        );
    }

private:

    static const float fColourRatio = 255.0;


}; // class OpenGLUtilsUtils 

}; // namespace Viewer

#endif // __Viewer_OpenGLUtilsUtils__
