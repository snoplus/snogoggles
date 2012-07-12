////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HitManager3d
///
/// \brief   Abstract class which is responsible for filtering
///	     and rendering hits.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
///     06/07/11 : Olivia Wasalski - FrontChecker3d is passed through a setter
///              instead of the constructor. \n
///     05/22/12 : Olivia Wasalski - FrontChecker3d removed. \n
///
/// \details 	The hit manager is responsible for: \n
///
///		Filtering hits (Uncalibrated, calibrated, etc.) . \n
///		Rendering hits. \n
///		Creating GUI objects which allow hit options to be processed. \n
///		Appropriately responding when passed Viewer::Events. \n
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_HitManager3d__
#define __Viewer_Frames_HitManager3d__

#include <Viewer/Module3d.hh>

#include <string>

namespace RAT {
    namespace DS {
        class PMTProperties;
    }; // namespace DS
}; // namespace RAT

namespace Viewer {
    namespace RIDS {
        class EV;
    }; // namespace RIDS

    class RenderState;

namespace Frames {

class HitManager3d : public Module3d {

public:

    virtual ~HitManager3d() { }

    static std::string TableName() { return "HitManager3d"; }
    std::string GetTableName() { return TableName(); }



}; // class HitManager3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_HitManager3d_hh
