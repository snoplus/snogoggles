#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultHits3d.hh>
#include <Viewer/Geodesic3d.hh>
#include <Viewer/HitsFrame3d.hh>

namespace Viewer {
namespace Frames {

HitsFrame3d::HitsFrame3d()
    : Specialized3d( Arcball3d::Name() + " " + DefaultHits3d::Name() + " NULL " + Geodesic3d::Name() ) { }

}; // namespace Frames
}; // namespace Viewer
