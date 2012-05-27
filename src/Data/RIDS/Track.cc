#include <RAT/DS/MCTrack.hh>
#include <Viewer/RIDS/Track.hh>

namespace Viewer {
namespace RIDS {

Track::Track( RAT::DS::MCTrack& rMCTrack )
{
    fParticleName = rMCTrack.GetParticleName(); 
    for( int i = 0; i < rMCTrack.GetMCTrackStepCount(); i++ )
        fTrackSteps.push_back( TrackStep( *rMCTrack.GetMCTrackStep( i ) ) );
}

Track::~Track()
{

}

const std::string& Track::GetParticleName() const
{
    return fParticleName;
}

const std::vector< TrackStep >& Track::GetTrackSteps() const
{
    return fTrackSteps;
}

}; // namespace RIDS
}; // namespace Viewer
