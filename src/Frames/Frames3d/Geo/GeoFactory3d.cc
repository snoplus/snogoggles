#include <Viewer/GeoFactory3d.hh>
#include <Viewer/GeoManager3d.hh>
#include <Viewer/Factory.hh>
#include <Viewer/Module3d.hh>

#include <Viewer/Geodesic3d.hh>
#include <Viewer/XML3d.hh>
#include <Viewer/GDML3d.hh>
#include <Viewer/RATGeo3d.hh>

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
    fFactory.Register( Geodesic3d::Name(), new Alloc<GeoManager3d, Geodesic3d>() );
    fFactory.Register( XML3d::Name(), new Alloc<GeoManager3d, XML3d>() );
    fFactory.Register( GDML3d::Name(), new Alloc<GeoManager3d, GDML3d>() );
    fFactory.Register( RATGeo3d::Name(), new Alloc<GeoManager3d, RATGeo3d>() );
}

GeoManager3d* GeoFactory3d::GetGeoManager( const std::string name )
{
    return fFactory.New( name );
}

}; // namespace Frames 
}; // namespace Viewer
