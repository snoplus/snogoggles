#include <vector>
#include <string>
#include <iostream>

#include <RAT/DS/Run.hh>

#include <Viewer/Module3d.hh>
#include <Viewer/CameraManager3d.hh>
#include <Viewer/HitManager3d.hh>
#include <Viewer/TrackManager3d.hh>
#include <Viewer/GeoManager3d.hh>
#include <Viewer/FitterManager3d.hh>
#include <Viewer/Axes3d.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/Rect.hh>
#include <Viewer/ModuleManager3d.hh>

namespace RAT {
    namespace DS {
        class PMTProperties;
    }; // namespace DS
}; // namespace RAT

namespace Viewer {
namespace Frames {

ModuleManager3d::ModuleManager3d()
{
	SetAllModules( NULL, NULL, NULL, NULL, NULL );
}

ModuleManager3d::~ModuleManager3d()
{
	DeleteAllModules();
}

void 
ModuleManager3d::SetAllModules( CameraManager3d* camera, 
                                HitManager3d* hits, 
                                TrackManager3d* tracks,
                                GeoManager3d* geo,
                                FitterManager3d* fitter )
{
    DeleteAllModules();
    fModules.push_back( camera );
    fModules.push_back( hits );
    fModules.push_back( tracks );
    fModules.push_back( geo );
    fModules.push_back( fitter );
	if( fModules[CAMERA] != NULL )
		fModules.push_back( new Axes3d( ((CameraManager3d*)fModules[CAMERA])->SuggestedAxisLength() ) );
    else
        fModules.push_back( NULL );
}

void ModuleManager3d::DeleteAllModules()
{
    for( int i = 0; i < fModules.size(); i++ )
    {
        delete fModules[i];
        fModules[i] = NULL;
    }
    fModules.clear();
}

void ModuleManager3d::LateInitialise()
{
	if( fModules[CAMERA] == NULL )
		throw NoCameraError();

	GeoManager3d::LoadFileSafe( (GeoManager3d*)fModules[GEO] );
}

void ModuleManager3d::LoadModuleConfigurations( const ConfigurationTable* configTable )
{
    for( int i = 0; i < fModules.size(); i++ )
        Module3d::LoadConfigurationSafe( fModules[i], configTable );
}

void ModuleManager3d::SaveModuleConfigurations( ConfigurationTable* configTable )
{
    for( int i = 0; i < fModules.size(); i++ )
        Module3d::SaveConfigurationSafe( fModules[i], configTable );
}

void ModuleManager3d::EventLoop()
{
    for( int i = 0; i < fModules.size(); i++ )
        Module3d::EventLoopSafe( fModules[i] );
}

void ModuleManager3d::ProcessData( const RenderState& renderState )
{
    for( int i = 0; i < fModules.size(); i++ )
        Module3d::ProcessDataSafe( fModules[i], renderState );
}

void ModuleManager3d::Render2d( RWWrapper& windowApp, const RenderState& renderState )
{

}

void ModuleManager3d::Render3d( RectPtr viewport, const RenderState& renderState )
{ 
    ((CameraManager3d*)(fModules[CAMERA]))->SetUpCameraSystem( viewport->GetRect( Rect::eGL ) ); 
    for( int i = 1; i < fModules.size(); i++ )
        Module3d::RenderSafe( fModules[i], renderState );
}

}; // namespace Frames
}; // namespace Viewer
