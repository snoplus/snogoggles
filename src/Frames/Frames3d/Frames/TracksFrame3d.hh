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
    inline sf::Rect< double > GetViewportRect();
    void CreateGUIObjects();

}; // class TracksFrame3d

std::string TracksFrame3d::Name()
{
    return "Tracks";
}

std::string TracksFrame3d::GetName()
{
    return Name();
}

sf::Rect< double > TracksFrame3d::GetViewportRect()
{
    return sf::Rect< double >( 0, 0.05, 0.8, 0.8 );
}

} // ::Frames3d
} // ::Viewer

#endif // __Viewer_Frames3d_TracksFrame3d__
