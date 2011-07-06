#include <Viewer/HitFactory3d.hh>
#include <Viewer/HitManager3d.hh>
#include <Viewer/Factory.hh>

namespace Viewer {
namespace Frames {

HitFactory3d* HitFactory3d::fInstance = NULL;

HitFactory3d* HitFactory3d::GetInstance()
{
    if( fInstance == NULL )
        {
            fInstance = new HitFactory3d();
        }
    return fInstance;
}

HitFactory3d::HitFactory3d()
{
    fFactory.Register( "null", new NullAlloc<HitManager3d>() );
}

HitManager3d* HitFactory3d::GetHitManager( const std::string name, FrontChecker3d* f )
{
    HitManager3d* h = fFactory.New( name );
    HitManager3d::SetFrontCheckerSafe( h, f );
    return h;
}

}; // namespace Frames 
}; // namespace Viewer
