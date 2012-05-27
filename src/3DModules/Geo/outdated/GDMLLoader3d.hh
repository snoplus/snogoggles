////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::GDMLLoader3d
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

#ifndef __Viewer_Frames_GDMLLoader3d__
#define __Viewer_Frames_GDMLLoader3d__

#include <string>
#include <map>

#include <Viewer/Polyhedron.hh>

class G4VPhysicalVolume;
class G4Polyhedron;

namespace Viewer {

    class World;
    class Volume;

namespace Frames {

class GDMLLoader3d {

public:

    GDMLLoader3d() { }
    World* GetWorld();

private:

    Volume CreateVolume( G4VPhysicalVolume* vol );
    Polyhedron CreatePolyhedron( G4Polyhedron *pol );

    static int fColour;

}; // class GDMLLoader3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_GDMLLoader3d__
