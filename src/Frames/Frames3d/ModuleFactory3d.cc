#include <Viewer/ModuleFactory3d.hh>
#include <Viewer/Manager3d.hh>
#include <Viewer/CameraFactory3d.hh>
#include <Viewer/HitFactory3d.hh>
#include <Viewer/TrackFactory3d.hh>
#include <Viewer/GeoFactory3d.hh>
#include <Viewer/FitterFactory3d.hh>
#include <Viewer/Module3d.hh>
#include <Viewer/ConfigurationTable.hh>

#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultHits3d.hh>

#include <vector>
#include <string>
#include <stdexcept>

namespace Viewer {
namespace Frames {

    class CameraManager3d;

ModuleFactory3d* ModuleFactory3d::fInstance = NULL;

ModuleFactory3d* ModuleFactory3d::GetInstance( )
{
    if( fInstance == NULL )
        fInstance = new ModuleFactory3d();

    return fInstance;
}

ModuleFactory3d::ModuleFactory3d( )
{
    fDefaultCameraManager = Arcball3d::Name();
    fDefaultHitManager = DefaultHits3d::Name();
    fDefaultTrackManager = Module3d::NullTag();
    fDefaultGeoManager = Module3d::NullTag();
    fDefaultFitterManager = Module3d::NullTag();
}

void ModuleFactory3d::SetAllModules( Manager3d* manager3d, std::vector<std::string>& modules )
{
    std::string cameraManager = fDefaultCameraManager;
    try { cameraManager = modules.at(0); }
    catch (std::out_of_range &e) { }

    std::string hitManager = fDefaultHitManager;
    try { hitManager = modules.at(1); }
    catch (std::out_of_range &e) { }

    std::string trackManager = fDefaultTrackManager;
    try { trackManager = modules.at(2); }
    catch (std::out_of_range &e) { }

    std::string geoManager = fDefaultGeoManager;
    try { geoManager = modules.at(3); }
    catch (std::out_of_range &e) { }

    std::string fitterManager = fDefaultFitterManager;
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

void ModuleFactory3d::SetAllModuleTypes( Manager3d* manager3d, ConfigurationTable& configTable )
{
    std::vector<std::string> modules;

    modules.push_back( GetModuleType( configTable, CameraManager3d::TableName(), fDefaultCameraManager ) );
    modules.push_back( GetModuleType( configTable, HitManager3d::TableName(), Module3d::NullTag() ) );
    modules.push_back( GetModuleType( configTable, TrackManager3d::TableName(), Module3d::NullTag() ) );
    modules.push_back( GetModuleType( configTable, GeoManager3d::TableName(), Module3d::NullTag() ) );
    modules.push_back( GetModuleType( configTable, FitterManager3d::TableName(), Module3d::NullTag() ) );

    manager3d->DeleteAllModules();
    SetAllModules( manager3d, modules );
}

std::string ModuleFactory3d::GetModuleType( ConfigurationTable& configTable, const std::string& tableName, const std::string& defaultName )
{
    std::string result;
    try { result = configTable.GetTable( tableName )->GetS( Module3d::MODULE_TAG ); }
    catch( ConfigurationTable::NoTableError& e ) { result = defaultName; }
    return result;
}

}; // namespce Frames
}; // namespace Viewer
