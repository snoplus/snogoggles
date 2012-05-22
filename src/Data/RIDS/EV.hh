////////////////////////////////////////////////////////////////////
/// \class EV
///
/// \brief  EV data structure
///          
/// \author Phil Jones <p.g.jones@qmul.ac.uk>                                                                                                    
///
/// REVISION HISTORY:\n
///     07/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail ROOT has many memory management issues, thus a ROOT 
///         independent data structure exists. This is the EV side 
///         data holder class.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_EV__
#define __Viewer_RIDS_EV__

#include <vector>

#include <Viewer/RIDS/PMTHit.hh>

namespace RAT
{
namespace DS
{
  class EV;
}
}

namespace Viewer
{
namespace RIDS
{

class EV
{
public:
  EV( RAT::DS::EV& rEV );
  ~EV();

  int GetGTID() const { return fGTID; }
  /// Return a vector of PMTHits (data) by source, e.g. eCal
  std::vector<PMTHit> GetHitData( EDataSource source ) const;

private:
  EV();
  
  std::vector<PMTHit> fCalHits;
  std::vector<PMTHit> fUnCalHits;
  std::vector<PMTHit> fTruthHits;

  unsigned long long fClock50;
  unsigned long long fClock10;
  int fTriggerWord;
  int fGTID;
};

} // namespace RIDS

} // namespace Viewer

#endif
