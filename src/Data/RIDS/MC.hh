////////////////////////////////////////////////////////////////////
/// \class MC
///
/// \brief  MC data structure
///          
/// \author Phil Jones <p.g.jones@qmul.ac.uk>                                                                                                    
///
/// RMCISION HISTORY:\n
///     07/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail ROOT has many memory management issues, thus a ROOT 
///         independent data structure exists. This is the MC side 
///         data holder class.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_MC__
#define __Viewer_RIDS_MC__

#include <vector>

#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/RIDS/Track.hh>

namespace RAT
{
namespace DS
{
  class MC;
}
}

namespace Viewer
{
namespace RIDS
{

class MC
{
public:
  MC( RAT::DS::MC& rMC );
  ~MC();

  /// Return a vector of PMTHits (data) by source, e.g. eCal
  std::vector<PMTHit> GetData( EDataSource source );

  inline std::vector<Track>& GetTracks() { return fTracks; }

private:
  MC();
  
  std::vector<PMTHit> fHits;
  std::vector<Track> fTracks;
};

} // namespace RIDS

} // namespace Viewer

#endif
