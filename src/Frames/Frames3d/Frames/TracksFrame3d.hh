////////////////////////////////////////////////////////////////////////
/// \class TracksFrame3d
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///                          <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     27/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames3d_TracksFrame3d__
#define __Viewer_Frames3d_TracksFrame3d__

#include <Viewer/Specialized3d.hh>

namespace Viewer {
namespace Frames {

class TracksFrame3d : public Specialized3d {
public:
    TracksFrame3d();
    static inline std::string Name();
    inline std::string GetName();

}; // class TracksFrame3d

std::string TracksFrame3d::Name()
{
    return "Tracks";
}

std::string TracksFrame3d::GetName()
{
    return Name();
}

} // ::Frames3d
} // ::Viewer

#endif // __Viewer_Frames3d_TracksFrame3d__
