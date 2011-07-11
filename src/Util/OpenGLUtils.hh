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

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <TVector3.h>
#include <TMath.h>

namespace Viewer {

class OpenGLUtils {

public:

    static inline void SetColour( const sf::Color& colour )
    {
        glColor4f( 
            colour.r/fColourRatio,
            colour.g/fColourRatio,
            colour.b/fColourRatio,
            colour.a/fColourRatio
        );
    }

    static inline void RotateGLMatrix( const TVector3& initialVector, const TVector3& finalVector )
    {
        TVector3 v1 = initialVector.Unit();
        TVector3 final = finalVector.Unit();

        TVector3 v2 = final - (v1*final) * v1;
        v2 = v2.Unit();
        TVector3 v3 = v1.Cross(v2);
        v3 = v3.Unit();
        Double_t angle = v1.Angle(final);

        glRotatef(angle * 180 / TMath::Pi(), v3.X(), v3.Y(), v3.Z()); 
    }

private:

    static const float fColourRatio = 255.0;


}; // class OpenGLUtils

}; // namespace Viewer

#endif // __Viewer_OpenGLUtils__
