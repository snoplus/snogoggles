#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/TracksFrame3d.hh>

namespace Viewer {
namespace Frames {

TracksFrame3d::TracksFrame3d()
    : Specialized3d( Arcball3d::Name() + " NULL " + DefaultTracks3d::Name() + " " + Geodesic3d::Name() ) { }

}; // namespace Frames
}; // namespace Viewer
