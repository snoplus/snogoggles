#include <sstream>
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
Time::GetDate()
{
  stringstream text;
  text << fYear << "/" << fMonth << "/" << fDay;
  return text.str();
}

string 
Time::GetTime()
{
  stringstream text;
  text << fHour << ":" << fMin << ":" << fSec;
  return text.str();
}
