////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::TrackManager3d
///
/// \brief   Abstract class which is responsible for filtering
///	     and rendering tracks.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
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

namespace RAT {
    namespace DS {
        class MC;
    };
};

namespace Viewer {
namespace Frames {

    class FrontChecker3d;

  class TrackManager3d : public Module3d {

public:

    /// Stores the IFrontChecker3d object.
    TrackManager3d( FrontChecker3d* f ) { fFront = f; }

    virtual ~TrackManager3d() { }

    static std::string TableName() { return "TrackManager3d"; }
    std::string GetTableName() { return TableName(); }

    /// Renders tracks.
    virtual void RenderTracks( RAT::DS::MC* mc ) = 0;

    static inline void RenderTracksSafe( TrackManager3d* t, RAT::DS::MC* mc )
    {
        if( t != NULL )
            t->RenderTracks( mc );
    }

protected:

    FrontChecker3d* fFront; ///< The front checker.


}; // class TrackManager3d

}; // namesapce Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_TrackManager3d__
