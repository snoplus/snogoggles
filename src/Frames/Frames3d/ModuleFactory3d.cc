#include <Viewer/ModuleFactory3d.hh>
#include <Viewer/Manager3d.hh>
#include <Viewer/CameraFactory3d.hh>
#include <Viewer/HitFactory3d.hh>
#include <Viewer/TrackFactory3d.hh>
#include <Viewer/GeoFactory3d.hh>
#include <Viewer/FitterFactory3d.hh>

#include <Viewer/Arcball3d.hh>

#include <vector>
#include <string>
#include <stdexcept>

namespace Viewer {
namespace Frames {

    class CameraManager3d;

void ModuleFactory3d::SetAllModules( Manager3d* manager3d, std::vector<std::string>& modules )
{
    std::string cameraManager = Arcball3d::Name();
    try { cameraManager = modules.at(0); }
    catch (std::out_of_range &e) { }

    std::string hitManager = "null";
    try { hitManager = modules.at(1); }
    catch (std::out_of_range &e) { }

    std::string trackManager = "null";
    try { trackManager = modules.at(2); }
    catch (std::out_of_range &e) { }

    std::string geoManager = "null";
    try { geoManager = modules.at(3); }
    catch (std::out_of_range &e) { }

    std::string fitterManager = "null";
    try { fitterManager = modules.at(4); }
    catch (std::out_of_range &e) { }

    CameraManager3d* c = CameraFactory3d::GetInstance()->GetCameraManager( cameraManager );

    manager3d->SetAllModules(
        c,
        HitFactory3d::GetInstance()->GetHitManager( hitManager, c ),
        TrackFactory3d::GetInstance()->GetTrackManager( trackManager, c ),
        GeoFactory3d::GetInstance()->GetGeoManager( geoManager ),
        FitterFactory3d::GetInstance()->GetFitterManager( fitterManager )
    );

}

}; // namespce Frames
}; // namespace Viewer
