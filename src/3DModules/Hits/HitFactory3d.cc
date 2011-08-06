#include <Viewer/HitFactory3d.hh>
#include <Viewer/HitManager3d.hh>
#include <Viewer/Factory.hh>
#include <Viewer/Module3d.hh>

#include <Viewer/DefaultHits3d.hh>

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
    fFactory.Register( Module3d::NullTag(), new NullAlloc<HitManager3d>() );
    fFactory.Register( DefaultHits3d::Name(), new Alloc<HitManager3d, DefaultHits3d>() );
}

HitManager3d* HitFactory3d::GetHitManager( const std::string name, FrontChecker3d* f )
{
    HitManager3d* h = fFactory.New( name );
    HitManager3d::SetFrontCheckerSafe( h, f );
    return h;
}

}; // namespace Frames 
}; // namespace Viewer
