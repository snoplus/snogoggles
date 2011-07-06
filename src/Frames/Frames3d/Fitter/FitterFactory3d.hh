////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames3d::FitterFactory3d
///
/// \brief Singleton factory that creates all fitter managers
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     05/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames3d_FitterFactory3d__
#define __Viewer_Frames3d_FitterFactory3d__

#include <Viewer/Factory.hh>
#include <Viewer/FitterManager3d.hh>

namespace Viewer {
namespace Frames3d {

class FitterFactory3d {

public:

    static FitterFactory3d* GetInstance();

    FitterManager3d* GetFitterManager( const std::string name );

private:

    FitterFactory3d();

    Factory<FitterManager3d> fFactory;

    static FitterFactory3d* fInstance;


}; // class FitterFactory

}; // namespace Frames3d 
}; // namespace Viewer

#endif // __Viewer_Frames3d_FitterFactory3d__
