////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::XMLLoader3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	19/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_XMLLoader3d__
#define __Viewer_Frames_XMLLoader3d__

#include <Viewer/WorldLoader3d.hh>
#include <string>

namespace Viewer {

    class World;
    class ConfigurationTable;

namespace Frames {

class XMLLoader3d : public WorldLoader3d {

public:

    XMLLoader3d() : WorldLoader3d() { }
    XMLLoader3d( const std::string& filename ) 
        : WorldLoader3d( filename ) { }
    virtual World* GetWorld();

}; // class XMLLoader3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_XMLLoader3d__
