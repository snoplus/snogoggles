////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::XML3d
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

#ifndef __Viewer_Frames_XML3d__
#define __Viewer_Frames_XML3d__

#include <Viewer/WorldBase3d.hh>
#include <Viewer/XMLLoader3d.hh>
#include <Viewer/WorldManager3d.hh>
#include <string>

namespace Viewer {
namespace Frames {

class XML3d : public WorldBase3d {

public:

    XML3d() : WorldBase3d( new XMLLoader3d( ), new WorldManager3d ) { }

    static std::string Name() { return "XML"; }
    std::string GetName() { return Name(); }

}; // class XML3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_XML3d__
