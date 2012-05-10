////////////////////////////////////////////////////////////////////
/// \class PMTHit
///
/// \brief  PMTHit data structure
///          
/// \author Phil Jones <p.g.jones@qmul.ac.uk>                                                                                                    
///
/// REVISION HISTORY:\n
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

// Special Python object forward declaration
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif

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
  PMTHit( double tac,
          double qhl,
          double qhs,
          double qlx );
  PMTHit( RAT::DS::PMTCal* rPMTCal );
  PMTHit( RAT::DS::PMTUnCal* rPMTUnCal );
  PMTHit( RAT::DS::PMTTruth* rPMTTruth );
  PMTHit( RAT::DS::MCPMT* rMCPMT );
  PMTHit( PyObject* pData, 
          int lcn );
  ~PMTHit();

  int GetLCN() const { return fLCN; }
  double GetTAC() const { return fTAC; }
  double GetQHL() const { return fQHL; }
  double GetQHS() const { return fQHS; }
  double GetQLX() const { return fQLX; }
  
  /// Get the data by the type, e.g. eTAC
  double GetData( EDataType type ) const;
  /// Return the data as a PyList (for python scripting)
  PyObject* NewPyList();

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
