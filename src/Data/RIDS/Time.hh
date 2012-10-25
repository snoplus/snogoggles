////////////////////////////////////////////////////////////////////
/// \class Time
///
/// \brief  Time data structure
///
/// \author P G Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     25 Oct 2012 : P.G.Jones - First Revision, new file. \n
///
/// \detail Generalised time structure that can deal with the SNO
///         and tm structures.
///
////////////////////////////////////////////////////////////////////

#ifndef __Viewer_RIDS_Time__
#define __Viewer_RIDS_Time__

#include <string>
#include <ctime>

namespace Viewer 
{
namespace RIDS 
{

class Time 
{
public:
  Time() { }
  Time( int UTDays, int UTSecs, int UTNsecs );
  Time( struct tm* tm );
  ~Time() { }

  std::string GetDate();
  std::string GetTime();
private:
  int fYear;
  int fMonth;
  int fDay;
  int fHour;
  int fMin;
  int fSec;
  int fNanoSec;
}; // class Time

} // namespace RIDS

} // namespace Viewer

#endif
