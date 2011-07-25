#include <TMath.h>
#include <TVector3.h>
#include <SFML/OpenGL.hpp>

#include <Viewer/OpenGLUtils.hh>

namespace Viewer {

void OpenGLUtils::RotateGLMatrix( const TVector3& initialVector, const TVector3& finalVector )
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

}; // namespace Viewer
