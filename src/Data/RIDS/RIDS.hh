////////////////////////////////////////////////////////////////////
/// \name RIDS
///
/// \brief  RIDS include
///          
/// \author Phil Jones <p.g.jones@qmul.ac.uk>                                                                                                                         
///
/// REVISION HISTORY:\n
///     07/05/12 : P.Jones - First Revision, new file. \n
///
/// \detail ROOT has many memory management issues, thus a ROOT 
///         independent data structure exists. This is the event 
///         definition information.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_RIDS__
#define __Viewer_RIDS_RIDS__

namespace Viewer
{
namespace RIDS
{
  enum EDataType { eTAC, eQHL, eQHS, eQLX };
  enum EDataSource { eMC, eTruth, eUnCal, eCal, eScript };

} // namespace RIDS

} // namespace Viewer

#endif
