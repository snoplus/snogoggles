////////////////////////////////////////////////////////////////////////
/// \class Combo3d
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

#ifndef __Viewer_Frames3d_Combo3d__
#define __Viewer_Frames3d_Combo3d__

#include <Viewer/Manager3d.hh>

namespace Viewer {
namespace Frames {

class Combo3d : public Manager3d {
public:
    Combo3d( const std::string& options ) 
        : Manager3d( options ) { }
    static inline std::string Name();
    inline std::string GetName();

}; // class Combo3d

std::string Combo3d::Name()
{
    return "3D-Combo";
}

std::string Combo3d::GetName()
{
    return Name();
}

} // ::Frames3d
} // ::Viewer

#endif // __Viewer_Frames3d_Combo3d__
