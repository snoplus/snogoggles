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
  Time( unsigned long long count10MHz );
  Time( struct tm* tm );
  ~Time() { }

  int operator- ( const Time& rhs ) const;
  bool operator>( const Time& rhs ) const;
  bool operator>=( const Time& rhs ) const;
  bool operator<( const Time& rhs ) const;
  bool operator<=( const Time& rhs ) const;
  bool operator==( const Time& rhs ) const;

  /// Return a string stating the difference in time to rhs
  std::string DiffTime( const Time& rhs ) const;
  std::string GetDate() const;
  std::string GetTime() const;
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
