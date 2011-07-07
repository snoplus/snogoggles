////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::GeoFactory3d
///
/// \brief Singleton factory that creates all geometry managers
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

#ifndef __Viewer_Frames_GeoFactory3d__
#define __Viewer_Frames_GeoFactory3d__

#include <Viewer/Factory.hh>
#include <Viewer/GeoManager3d.hh>

namespace Viewer {
namespace Frames {

class GeoFactory3d {

public:

    static GeoFactory3d* GetInstance();

    GeoManager3d* GetGeoManager( const std::string name );

private:

    GeoFactory3d();

    Factory<GeoManager3d> fFactory;

    static GeoFactory3d* fInstance;


}; // class GeoFactory

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_GeoFactory3d__
