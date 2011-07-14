#include <Viewer/GeoFactory3d.hh>
#include <Viewer/GeoManager3d.hh>
#include <Viewer/Factory.hh>
#include <Viewer/Module3d.hh>

namespace Viewer {
namespace Frames {

GeoFactory3d* GeoFactory3d::fInstance = NULL;

GeoFactory3d* GeoFactory3d::GetInstance()
{
    if( fInstance == NULL )
        {
            fInstance = new GeoFactory3d();
        }
    return fInstance;
}

GeoFactory3d::GeoFactory3d()
{
    fFactory.Register( Module3d::NullTag(), new NullAlloc<GeoManager3d>() );
}

GeoManager3d* GeoFactory3d::GetGeoManager( const std::string name )
{
    return fFactory.New( name );
}

}; // namespace Frames 
}; // namespace Viewer
