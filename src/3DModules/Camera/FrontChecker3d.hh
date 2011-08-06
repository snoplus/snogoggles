////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::FrontChecker3d
///
/// \brief   Checks whether a given vector is in the front half
///	     of the scene.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
///
/// \details 	Used to encapsulate the camera manager so that none of 
///		the other modules can access any other members of the
///		camera manager except for this method.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_FrontChecker3d__
#define __Viewer_Frames_FrontChecker3d__

#include <TVector3.h>

namespace Viewer {
namespace Frames {

class FrontChecker3d {

public:

/// Checks whether the given vector is in the front half or the back half of the scene.
virtual bool IsFront( const TVector3& v ) = 0;

}; // class FrontChecker3d

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_FrontChecker3d__
