////////////////////////////////////////////////////////////////////
/// \class PMTHit
///
/// \brief  PMTHit data structure
///          
/// \author Phil Jones <p.g.jones@qmul.ac.uk>                                                                                                    
///
/// RPMTHitISION HISTORY:\n
///     07/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail ROOT has many memory management issues, thus a ROOT 
///         independent data structure exists. This is the generic
///         PMTHit data holder class.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_PMTHit__
#define __Viewer_RIDS_PMTHit__

#include <Viewer/RIDS/RIDS.hh>

namespace RAT
{
namespace DS
{
  class PMTCal;
  class PMTUnCal;
  class MCPMT;
  class PMTTruth;
}
}

namespace Viewer
{
namespace RIDS
{

class PMTHit
{
public:
  PMTHit( RAT::DS::PMTCal* rPMTCal );
  PMTHit( RAT::DS::PMTUnCal* rPMTUnCal );
  PMTHit( RAT::DS::PMTTruth* rPMTTruth );
  PMTHit( RAT::DS::MCPMT* rMCPMT );
  ~PMTHit();

  int GetLCN() { return fLCN; }
  double GetTAC() { return fTAC; }
  double GetQHL() { return fQHL; }
  double GetQHS() { return fQHS; }
  double GetQLX() { return fQLX; }
  
  /// Get the data by the type, e.g. eTAC
  double GetData( EDataType type );

private:
  PMTHit();

  int fLCN; /// < PMTHit Logical channel number
  double fTAC; /// < The TAC aspect
  double fQHL; /// < The QHL aspect (MCPMT data only has 1 charge)
  double fQHS; /// < The QHS aspect (MCPMT data only has 1 charge)
  double fQLX; /// < The QLX aspect (MCPMT data only has 1 charge)
};

} // namespace RIDS

} // namespace Viewer

#endif
