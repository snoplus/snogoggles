////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames3d::HitManager3d
///
/// \brief   Abstract class which is responsible for filtering
///	     and rendering hits.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
///
/// \details 	The hit manager is responsible for: \n
///
///		Filtering hits (Uncalibrated, calibrated, etc.) . \n
///		Rendering hits. \n
///		Creating GUI objects which allow hit options to be processed. \n
///		Appropriately responding when passed Viewer::Events. \n
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames3d_HitManager3d__
#define __Viewer_Frames3d_HitManager3d__

#include <Viewer/Module3d.hh>
#include <Viewer/FrontChecker3d.hh>

#include <string>

namespace RAT {
    namespace DS {
        class EV;
        class PMTProperties;
    };
};

namespace Viewer {

namespace Frames3d {

    class FrontChecker3d;

class HitManager3d : public Module3d {

public:

    /// Stores the FrontChecker3d object.
    HitManager3d( FrontChecker3d* f ) { fFront = f; }

    virtual ~HitManager3d() { }

    static std::string TableName() { return "HitManager3d"; }
    std::string GetTableName() { return TableName(); }

    /// Renders hits.
    virtual void RenderHits( RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList ) = 0;
    static inline void RenderHitsSafe( HitManager3d* h, RAT::DS::EV* ev, RAT::DS::PMTProperties* pmtList )
    {
        if( h != NULL )
            h->RenderHits( ev, pmtList );
    }

protected:

    FrontChecker3d* fFront; ///< The front checker.


}; // class HitManager3d

}; // namespace Frames3d 
}; // namespace Viewer

#endif // Viewer_Frames3d_HitManager3d_hh
