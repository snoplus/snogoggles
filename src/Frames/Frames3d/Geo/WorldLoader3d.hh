////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::WorldLoader3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	21/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_WorldLoader3d__
#define __Viewer_Frames_WorldLoader3d__

#include <string>

namespace Viewer {

    class World;
    class ConfigurationTable;

namespace Frames {

class WorldLoader3d {

public:

    WorldLoader3d( );
    WorldLoader3d( const std::string& filename );
    virtual ~WorldLoader3d() { }
    virtual void LoadConfiguration( ConfigurationTable* configTable );
    virtual void SaveConfiguration( ConfigurationTable* configTable );
    virtual World* GetWorld() = 0;

protected:

    std::string fFilename;
    bool fLoadFilename;

    static const std::string FILENAME;

}; // class WorldLoader3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_WorldLoader3d__
