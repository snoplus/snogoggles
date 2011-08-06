#include <Viewer/CameraFactory3d.hh>
#include <Viewer/HitFactory3d.hh>
#include <Viewer/TrackFactory3d.hh>
#include <Viewer/GeoFactory3d.hh>
#include <Viewer/FitterFactory3d.hh>
#include <Viewer/ModuleManager3d.hh>
#include <Viewer/ModuleManagerFactory3d.hh>

namespace Viewer {
namespace Frames {

ModuleManagerFactory3d* ModuleManagerFactory3d::fInstance = NULL;

ModuleManagerFactory3d::ModuleManagerFactory3d()
{

}

ModuleManagerFactory3d* ModuleManagerFactory3d::GetInstance()
{
	if( fInstance == NULL )
		fInstance = new ModuleManagerFactory3d();
	return fInstance;
}

ModuleManager3d* ModuleManagerFactory3d::New(
	const std::string& camera,
	const std::string& hits,
	const std::string& tracks,
	const std::string& geo,
	const std::string& fitter
)
{
	ModuleManager3d* m = new ModuleManager3d();
	CameraManager3d* c = CameraFactory3d::GetInstance()->GetCameraManager( camera );
	m->SetAllModules(
		c,
		HitFactory3d::GetInstance()->GetHitManager( hits, c ),
		TrackFactory3d::GetInstance()->GetTrackManager( tracks, c ),
		GeoFactory3d::GetInstance()->GetGeoManager( geo ),
		FitterFactory3d::GetInstance()->GetFitterManager( fitter )
	);
	return m;
}

}; // namespace Viewer
}; // namespace Frames

