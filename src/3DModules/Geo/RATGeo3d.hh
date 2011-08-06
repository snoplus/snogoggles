////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::RATGeo3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	27/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_RATGeo3d__
#define __Viewer_Frames_RATGeo3d__

#include <Viewer/WorldBase3d.hh>
#include <Viewer/GDMLLoader3d.hh>
#include <Viewer/WorldManager3d.hh>
#include <string>

namespace Viewer {
namespace Frames {

class RATGeo3d : public WorldBase3d {

public:

    RATGeo3d() : 
        WorldBase3d( new GDMLLoader3d( "snoplus_noPMTs.gdml" ), new WorldManager3d ) { }

    static std::string Name() { return "RATGeo"; }
    std::string GetName() { return Name(); }

}; // class RATGeo

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_RATGeo3d__
