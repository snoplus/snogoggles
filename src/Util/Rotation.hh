////////////////////////////////////////////////////////////////////////
/// \class Viewer::Rotation
///
/// \brief   Contains information to rotate TVector3
///
/// \author  Olivia Wasalski <wasalski@berkeley.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/22/12 : Olivia Wasalski - First Revision, New File. \n
///
/// \detail  As Brief.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Rotation__
#define __Viewer_Rotation__

#include <TVector3.h>

namespace Viewer {

class Rotation
{
public:
    Rotation() {}
    Rotation( TVector3 axis, double angle );
    void Rotate( TVector3& v );
    void GLRotate();

private:
    TVector3 fAxis;
    double fAngle;

}; // class Rotation

}; // namespace Viewer

#endif // __Viewer_Rotation__
