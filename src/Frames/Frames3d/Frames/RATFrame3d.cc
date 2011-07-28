#include <Viewer/Arcball3d.hh>
#include <Viewer/RATGeo3d.hh>
#include <Viewer/RATFrame3d.hh>

namespace Viewer {
namespace Frames {

RATFrame3d::RATFrame3d()
    : Specialized3d( Arcball3d::Name() + " NULL NULL " + RATGeo3d::Name() ) { }


}; // namespace Frames
}; // namespace Viewer
