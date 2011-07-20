////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::XML3d
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


#ifndef __Viewer_Frames_XML3d__
#define __Viewer_Frames_XML3d__

#include <Viewer/VolumeManager3d.hh>
#include <string>

namespace Viewer {

    class Volume;

namespace Frames {

class XML3d : public VolumeManager3d {

public:

    virtual ~XML3d() { }

    /// Renders the geometry.

    virtual Volume* GetVolume();

    virtual std::string GetFilename() = 0;

}; // class XML3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_XML3d__
