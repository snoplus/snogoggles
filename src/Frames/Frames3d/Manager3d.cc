#include <Viewer/Manager3d.hh>
#include <Viewer/CameraManager3d.hh>
#include <Viewer/HitManager3d.hh>
#include <Viewer/TrackManager3d.hh>
#include <Viewer/GeoManager3d.hh>
#include <Viewer/FitterManager3d.hh>
#include <Viewer/StringUtils.hh>
#include <Viewer/ModuleFactory3d.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/EventData.hh>

#include <vector>
#include <string>

namespace RAT {
    namespace DS {
        class EV;
        class PMTProperties;
    }; // namespace DS
}; // namespace RAT

namespace Viewer {
namespace Frames3d {

Manager3d::Manager3d()
{
    SetAllModules( NULL, NULL, NULL, NULL, NULL );
}

Manager3d::Manager3d( const std::string& options )
{
    Manager3d();
    std::vector<std::string> tokens;
    StringUtils::SplitString( options, " ", tokens );
    ModuleFactory3d::SetAllModules( this, tokens );
}

Manager3d::~Manager3d()
{
    delete fCameraManager;    fCameraManager = NULL; 
    delete fHitManager;       fHitManager = NULL; 
    delete fTrackManager;     fTrackManager = NULL;
    delete fGeoManager;       fGeoManager = NULL;
    delete fFitterManager;    fFitterManager = NULL;
}

void Manager3d::SetAllModules( CameraManager3d* camera, HitManager3d* hits, TrackManager3d* tracks, GeoManager3d* geo, FitterManager3d* fitter)
{
    fCameraManager = camera;
    fHitManager = hits;
    fTrackManager = tracks;
    fGeoManager = geo;
    fFitterManager = fitter;
}

void Manager3d::Initialize( ConfigurationTable& configTable ) 
{
    CreateGUIObjects();
    LoadConfiguration( configTable );
}

void Manager3d::CreateGUIObjects()
{

}

void Manager3d::LoadConfiguration( ConfigurationTable& configTable )
{
    Module3d::LoadConfigurationSafe( fCameraManager, configTable );
    Module3d::LoadConfigurationSafe( fHitManager, configTable );
    Module3d::LoadConfigurationSafe( fTrackManager, configTable );
    Module3d::LoadConfigurationSafe( fGeoManager, configTable );
    Module3d::LoadConfigurationSafe( fFitterManager, configTable );
}

void Manager3d::SaveConfiguration( ConfigurationTable& configTable ) 
{
    Module3d::SaveConfigurationSafe( fCameraManager, configTable );
    Module3d::SaveConfigurationSafe( fHitManager, configTable );
    Module3d::SaveConfigurationSafe( fTrackManager, configTable );
    Module3d::SaveConfigurationSafe( fGeoManager, configTable );
    Module3d::SaveConfigurationSafe( fFitterManager, configTable );
}

void Manager3d::EventLoop() 
{
    while( !fEvents.empty() )
    {
        Module3d::EventLoopSafe( fCameraManager, fEvents.front() );
        Module3d::EventLoopSafe( fHitManager, fEvents.front() );
        Module3d::EventLoopSafe( fTrackManager, fEvents.front() );
        Module3d::EventLoopSafe( fGeoManager, fEvents.front() );
        Module3d::EventLoopSafe( fFitterManager, fEvents.front() );

        fEvents.pop();
    }
}

void Manager3d::Render3d( RWWrapper& windowApp ) 
{
    RAT::DS::EV* ev = EventData::GetInstance().GetCurrentEV();
    RAT::DS::PMTProperties* pmtList = EventData::GetInstance().GetPMTList();

    fCameraManager->SetUpCameraSystem( fFrameCoord.Get3dViewport() );
    HitManager3d::RenderHitsSafe( fHitManager, ev, pmtList );
    // TrackManager3d::RenderTracksSafe( fTrackManager, mc );
    GeoManager3d::RenderGeometrySafe( fGeoManager );
    FitterManager3d::RenderFitVertexSafe( fFitterManager );
}

}; // namespace Frames3d
}; // namespace Viewer
