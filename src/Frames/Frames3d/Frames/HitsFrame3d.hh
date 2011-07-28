////////////////////////////////////////////////////////////////////////
/// \class HitsFrame3d
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

#ifndef __Viewer_Frames3d_HitsFrame3d__
#define __Viewer_Frames3d_HitsFrame3d__

#include <Viewer/Specialized3d.hh>

namespace Viewer {
namespace Frames {

class HitsFrame3d : public Specialized3d {
public:
    HitsFrame3d();
    static inline std::string Name();
    inline std::string GetName();
    void CreateGUIObjects();
    inline sf::Rect< double > GetViewportRect();

}; // class HitsFrame3d

std::string HitsFrame3d::Name()
{
    return "Hits";
}

std::string HitsFrame3d::GetName()
{
    return Name();
}

sf::Rect< double > HitsFrame3d::GetViewportRect()
{
    return sf::Rect< double >( 0, 0, 1, 0.88 );
}

} // ::Frames3d
} // ::Viewer

#endif // __Viewer_Frames3d_HitsFrame3d__
