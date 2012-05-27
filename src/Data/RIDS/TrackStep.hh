////////////////////////////////////////////////////////////////////
/// \class TrackStep
///
/// \brief  Track Step data structure
///
/// \author Olivia Wasalski <wasalski@berkeley.edu>
///
/// REVISION HISTORY:\n
///     May 23, 2012 : O.Wasalski - First Revision, new file. \n
///
/// \detail ROOT has many memory management issues, thus a ROOT 
///         independent data structure exists. This is the Track Step
///         data holder class.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_TrackStep__
#define __Viewer_RIDS_TrackStep__

#include <TVector3.h>

namespace RAT {
    namespace DS {
        class MCTrackStep;
    } // namespace DS
} // namespace RAT

namespace Viewer {
namespace RIDS {

class TrackStep {

public:
    TrackStep( RAT::DS::MCTrackStep& rMCTrackStep );
    ~TrackStep();
    const TVector3& GetEndPos() const;

private:
    float fLength;
    TVector3 fEndPos;

}; // class TrackStep

} // namespace RIDS

} // namespace Viewer

#endif
