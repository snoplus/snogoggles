////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::TrackManager3d
///
/// \brief   Abstract class which is responsible for filtering
///	     and rendering tracks.
///
/// \author Olivia Wasalski <wasalski@berkeley.ca>
///			    <oliviawasalski@gmail.ca>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
///     06/07/11 : Olivia Wasalski - FrontChecker3d is passed through a setter
///              instead of the constructor. \n
///     May 23, 2012 : O. Wasalski - RIDS data structure instead of RAT::DS
///
/// \details 	The track manager is responsible for: \n
///
///		Filtering tracks. \n
///		Rendering tracks. \n
///		Colour code tracks by particle type. \n
///		Creating GUI objects which allow track options to be processed. \n
///		Appropriately responding when passed Viewer::Events. \n
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_TrackManager3d__
#define __Viewer_Frames_TrackManager3d__

#include <Viewer/Module3d.hh>
#include <string>

namespace Viewer {
    namespace RIDS {
        class MC;
    }; // namespace RIDS

namespace Frames {

class TrackManager3d : public Module3d {

public:

    virtual ~TrackManager3d() { }

    static std::string TableName() { return "TrackManager3d"; }
    std::string GetTableName() { return TableName(); }

    /// Renders tracks.
    virtual void RenderTracks( RIDS::MC& mc, const RenderState& renderState ) = 0;

    static inline void RenderTracksSafe( TrackManager3d* t, RIDS::MC& mc, const RenderState& renderState )
    {
        if( t != NULL )
            t->RenderTracks( mc, renderState );
    }


}; // class TrackManager3d

}; // namesapce Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_TrackManager3d__
