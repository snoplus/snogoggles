#include <Viewer/TrackFactory3d.hh>
#include <Viewer/TrackManager3d.hh>
#include <Viewer/Factory.hh>
#include <Viewer/Module3d.hh>

#include <Viewer/DefaultTracks3d.hh>

namespace Viewer {
namespace Frames {

TrackFactory3d* TrackFactory3d::fInstance = NULL;

TrackFactory3d* TrackFactory3d::GetInstance()
{
    if( fInstance == NULL )
        {
            fInstance = new TrackFactory3d();
        }
    return fInstance;
}

TrackFactory3d::TrackFactory3d()
{
    fFactory.Register( Module3d::NullTag(), new NullAlloc<TrackManager3d>() );
    fFactory.Register( DefaultTracks3d::Name(), new Alloc<TrackManager3d, DefaultTracks3d>() );
}

TrackManager3d* TrackFactory3d::GetTrackManager( const std::string name, FrontChecker3d* f )
{
    TrackManager3d* t = fFactory.New( name );
    TrackManager3d::SetFrontCheckerSafe( t, f );
    return t;
}

}; // namespace Frames 
}; // namespace Viewer
