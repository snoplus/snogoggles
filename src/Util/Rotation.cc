#include <SFML/OpenGL.hpp>

#include <Viewer/Rotation.hh>

namespace Viewer {

Rotation::Rotation( TVector3 axis, double angle )
{
    fAxis = axis;
    fAngle = angle;
}

void Rotation::Rotate( TVector3& v ) const
{
    if( fAxis != TVector3() )
        v.Rotate( fAngle, fAxis );
}

void Rotation::GLRotate() const
{
    glRotatef( -180*fAngle/3.14159, fAxis.X(), fAxis.Y(), fAxis.Z() );
}

}; // namespace Viewer
