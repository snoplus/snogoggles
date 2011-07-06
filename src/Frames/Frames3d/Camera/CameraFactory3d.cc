#include <Viewer/CameraFactory3d.hh>
#include <Viewer/CameraManager3d.hh>
#include <Viewer/Factory.hh>

namespace Viewer {
namespace Frames3d {

CameraFactory3d* CameraFactory3d::fInstance = NULL;

CameraFactory3d* CameraFactory3d::GetInstance()
{
    if( fInstance == NULL )
        {
            fInstance = new CameraFactory3d();
        }
    return fInstance;
}

CameraFactory3d::CameraFactory3d()
{
    fFactory.Register( "null", new NullAlloc<CameraManager3d>() );
}

CameraManager3d* CameraFactory3d::GetCameraManager( const std::string name )
{
    return fFactory.New( name );
}

}; // namespce Frames3d
}; // namespace Viewer
