#include <Viewer/CameraFactory3d.hh>
#include <Viewer/CameraManager3d.hh>
#include <Viewer/Factory.hh>

#include <Viewer/Arcball3d.hh>

namespace Viewer {
namespace Frames {

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
    fFactory.Register( Arcball3d::Name(), new Alloc<CameraManager3d, Arcball3d>() );
}

CameraManager3d* CameraFactory3d::GetCameraManager( const std::string name )
{
    return fFactory.New( name );
}

}; // namespce Frames
}; // namespace Viewer
