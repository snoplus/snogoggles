////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::TrackFactory3d
///
/// \brief Singleton factory that creates all track managers
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/07/11 : Olivia Wasalski - First Revision, new file. \n
///     06/07/11 : Olivia Wasalski - Factory adds a front checker. \n
///
/// \detail 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_TrackFactory3d__
#define __Viewer_Frames_TrackFactory3d__

#include <Viewer/Factory.hh>
#include <Viewer/TrackManager3d.hh>

namespace Viewer {
namespace Frames {

    class FrontChecker3d;

class TrackFactory3d {

public:

    static TrackFactory3d* GetInstance();

    TrackManager3d* GetTrackManager( const std::string name, FrontChecker3d* f );

private:

    TrackFactory3d();

    Factory<TrackManager3d> fFactory;

    static TrackFactory3d* fInstance;


}; // class TrackFactory

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_TrackFactory3d__
