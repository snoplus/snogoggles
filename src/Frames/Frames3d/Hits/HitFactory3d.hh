////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HitFactory3d
///
/// \brief Singleton factory that creates all hit managers
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

#ifndef __Viewer_Frames_HitFactory3d__
#define __Viewer_Frames_HitFactory3d__

#include <Viewer/Factory.hh>
#include <Viewer/HitManager3d.hh>

namespace Viewer {
namespace Frames {

    class FrontChecker3d;

class HitFactory3d {

public:

    static HitFactory3d* GetInstance();

    HitManager3d* GetHitManager( const std::string name, FrontChecker3d* f );

private:

    HitFactory3d();

    Factory<HitManager3d> fFactory;

    static HitFactory3d* fInstance;


}; // class HitFactory

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_HitFactory3d__
