#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <limits.h>
using namespace std;

#include <Viewer/RIDS/Time.hh>
using namespace Viewer::RIDS;

Time::Time( unsigned long long count10MHz )
{
  struct tm tms;
  tms.tm_sec = 0;
  tms.tm_min = 0;
  tms.tm_hour = 0;
  tms.tm_mday = 1;
  tms.tm_mon = 0;
  tms.tm_year = 96;
  tms.tm_isdst = 0;
  time_t sno_time_zero = mktime(&tms);

  double evTime = count10MHz * 1e-7 + sno_time_zero;
  time_t the_time = (time_t)evTime;
  the_time -= 5 * 3600L; //DST
  //struct tm* tm = gmtime(&the_time); //DST
  struct tm* tm = localtime(&the_time);
  fYear = tm->tm_year + 1900;
  fMonth = tm->tm_mon;
  fDay = tm->tm_mday;
  fHour = tm->tm_hour;
  fMin = tm->tm_min;
  fSec = tm->tm_sec;
}

Time::Time( struct tm* tm )
{
  fYear = tm->tm_year + 1900;
  fMonth = tm->tm_mon;
  fDay = tm->tm_mday;
  fHour = tm->tm_hour;
  fMin = tm->tm_min;
  fSec = tm->tm_sec;
}

string 
Time::DiffTime( const Time& rhs ) const
{
  // Should display largest difference!
  stringstream text;
  if( fYear != rhs.fYear )
    text << abs( fYear - rhs.fYear ) << " years";
  else if( fMonth != rhs.fMonth )
    text << abs( fMonth - rhs.fMonth ) << " months";
  else if( fDay != rhs.fDay )
    text << abs( fDay - rhs.fDay ) << " days";
  else if( fHour != rhs.fHour )
    text << abs( fHour - rhs.fHour ) << " hours";
  else if( fMin != rhs.fMin )
    text << abs( fMin - rhs.fMin ) << " mins";
  else if( fSec != rhs.fSec )
    text << abs( fSec - rhs.fSec ) << " secs";
  //else if( fNSec != rhs.fNSec )
  //  text << scientific << abs( fNSec - rhs.fNSec ) << " ns";
  else
    text << "<1 second";
  return text.str();
}

string 
Time::GetDate() const 
{
  stringstream text;
  text << fYear << "/" << fMonth  + 1 << "/" << fDay; // Month is stored as months since January, thus Jan is stored as 0 Thus need +1
  return text.str();
}

string 
Time::GetTime() const
{
  stringstream text;
  text << fHour << ":" << fMin << ":" << fSec;
  return text.str();
}

int
Time::operator-( const Time& rhs ) const
{
  int date = fDay + fMonth * 1000 + fYear * 100000;
  int rhsDate = rhs.fDay + rhs.fMonth * 1000 + rhs.fYear * 100000;
  if( date != rhsDate )
    return INT_MAX;
  int time = fSec + fMin * 60 + fHour * 60 * 60;
  int rhsTime = rhs.fSec + rhs.fMin * 60 + rhs.fHour * 60 * 60;
  return time - rhsTime;
}

bool 
Time::operator>( const Time& rhs ) const
{
  int date = fDay + fMonth * 1000 + fYear * 100000;
  int rhsDate = rhs.fDay + rhs.fMonth * 1000 + rhs.fYear * 100000;
  if( date > rhsDate )
    return true;
  else if( date == rhsDate )
    {
      int time = fSec + fMin * 100 + fHour * 10000;
      int rhsTime = rhs.fSec + rhs.fMin * 100 + rhs.fHour * 10000;
      if( time > rhsTime )
        return true;
      else
        return false;
    }
  else
    return false;
}
bool 
Time::operator>=( const Time& rhs ) const
{

}

bool 
Time::operator<( const Time& rhs ) const
{

}

bool 
Time::operator<=( const Time& rhs ) const 
{

}

bool 
Time::operator==( const Time& rhs ) const
{

}
