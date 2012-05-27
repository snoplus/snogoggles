#include <RAT/DS/MCTrackStep.hh>
#include <Viewer/RIDS/TrackStep.hh>

namespace Viewer {
namespace RIDS {

TrackStep::TrackStep( RAT::DS::MCTrackStep& rMCTrackStep )
{
    fLength = rMCTrackStep.GetLength();
    fEndPos = rMCTrackStep.GetEndPos();
}

TrackStep::~TrackStep()
{

}

const TVector3& TrackStep::GetEndPos() const
{
    return fEndPos;
}

}; // namespace RIDS
}; // namespace Viewer
