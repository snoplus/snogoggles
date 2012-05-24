////////////////////////////////////////////////////////////////////
/// \class Track
///
/// \brief  Track data structure
///
/// \author Olivia Wasalski <wasalski@berkeley.edu>
///
/// REVISION HISTORY:\n
///     May 23, 2012 : O.Wasalski - First Revision, new file. \n
///
/// \detail ROOT has many memory management issues, thus a ROOT 
///         independent data structure exists. This is the track
///         data holder class.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_Track__
#define __Viewer_RIDS_Track__

#include <vector>
#include <string>

#include <Viewer/RIDS/TrackStep.hh>

namespace RAT {
    namespace DS {
        class MCTrack;
    } // namespace DS
} // namespace RAT

namespace Viewer {
namespace RIDS {

class Track {

public:
    Track( RAT::DS::MCTrack& rMCTrack );
    ~Track();
    const std::string& GetParticleName() const;
    const std::vector< TrackStep >& GetTrackSteps() const;

private:   
    std::string fParticleName;
    std::vector< TrackStep > fTrackSteps;

}; // class Track

} // namespace RIDS

} // namespace Viewer

#endif
