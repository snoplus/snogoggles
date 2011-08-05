////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::GDML3d
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

#ifndef __Viewer_Frames_GDML3d__
#define __Viewer_Frames_GDML3d__

#include <Viewer/WorldBase3d.hh>
#include <Viewer/GDMLLoader3d.hh>
#include <Viewer/WorldManager3d.hh>
#include <string>

namespace Viewer {
namespace Frames {

class GDML3d : public WorldBase3d {

public:

    GDML3d() : WorldBase3d( new GDMLLoader3d( ), new WorldManager3d ) { }

    static std::string Name() { return "GDML"; }
    std::string GetName() { return Name(); }

}; // class GDML3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_GDML3d__
