#include <Viewer/FitterFactory3d.hh>
#include <Viewer/FitterManager3d.hh>
#include <Viewer/Factory.hh>
#include <Viewer/Module3d.hh>

namespace Viewer {
namespace Frames {

FitterFactory3d* FitterFactory3d::fInstance = NULL;

FitterFactory3d* FitterFactory3d::GetInstance()
{
    if( fInstance == NULL )
        {
            fInstance = new FitterFactory3d();
        }
    return fInstance;
}

FitterFactory3d::FitterFactory3d()
{
    fFactory.Register( Module3d::NullTag(), new NullAlloc<FitterManager3d>() );
}

FitterManager3d* FitterFactory3d::GetFitterManager( const std::string name )
{
    return fFactory.New( name );
}

}; // namespace Frames 
}; // namespace Viewer
