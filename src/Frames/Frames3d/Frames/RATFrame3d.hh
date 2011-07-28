////////////////////////////////////////////////////////////////////////
/// \class RATFrame3d
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

#ifndef __Viewer_Frames3d_RATFrame3d__
#define __Viewer_Frames3d_RATFrame3d__

#include <Viewer/Specialized3d.hh>

namespace Viewer {
namespace Frames {

class RATFrame3d : public Specialized3d {
public:
    RATFrame3d();
    static inline std::string Name();
    inline std::string GetName();
    void CreateGUIObjects();
    inline sf::Rect< double > GetViewportRect();

}; // class RATFrame3d

std::string RATFrame3d::Name()
{
    return "RATGeometry";
}

std::string RATFrame3d::GetName()
{
    return Name();
}

sf::Rect< double > RATFrame3d::GetViewportRect()
{
    return sf::Rect< double >( 0, 0.05, 0.8, 0.8 );
}

} // ::Frames3d
} // ::Viewer

#endif // __Viewer_Frames3d_RATFrame3d__
