////////////////////////////////////////////////////////////////////////
/// \class Specialized3d
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

#ifndef __Viewer_Frames3d_Specialized3d__
#define __Viewer_Frames3d_Specialized3d__

#include <Viewer/Manager3d.hh>

namespace Viewer {
namespace Frames {

class Specialized3d : public Manager3d {
public:
    Specialized3d( const std::string& options )
        : Manager3d( options ) { }
    inline void LoadConfiguration( ConfigurationTable& configTable );

}; // class Specialized3d

void Specialized3d::LoadConfiguration( ConfigurationTable& configTable )
{
    LoadWithoutSettingModules( configTable );
}

} // ::Frames3d
} // ::Viewer

#endif // __Viewer_Frames3d_Specialized3d__
