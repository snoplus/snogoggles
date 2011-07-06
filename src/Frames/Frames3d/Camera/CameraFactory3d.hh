////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames3d::CameraFactory3d
///
/// \brief Singleton factory that creates all camera managers
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames3d_CameraFactory3d__
#define __Viewer_Frames3d_CameraFactory3d__

#include <Viewer/Factory.hh>
#include <Viewer/CameraManager3d.hh>

namespace Viewer {
namespace Frames3d {

class CameraFactory3d {

public:

    static CameraFactory3d* GetInstance();

    CameraManager3d* GetCameraManager( const std::string name );

private:

    CameraFactory3d();

    Factory<CameraManager3d> fFactory;

    static CameraFactory3d* fInstance;


}; // class CameraFactory

}; // namespace Frames3d
}; // namespace Viewer

#endif // __Viewer_Frames3d_CameraFactory3d__
