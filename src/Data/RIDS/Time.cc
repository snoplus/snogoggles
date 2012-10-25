#include <sstream>
using namespace std;

#include <Viewer/RIDS/Time.hh>
using namespace Viewer::RIDS;

Time::Time( int UTDays, 
            int UTSecs, 
            int UTNsecs )
{
  const double jddOffset = 2455197.50;
  double d2010 = (double)(int)jddOffset + 1.;
  double jdd = d2010 + double(UTDays) + double(UTSecs)/86400. + UTNsecs/(86400.*1.0e+09);

  int i = int(jdd);
  double a = double(int((i - 1867216.25) /36524.25 ));
  double b = double(i + 1 + a - int(a/4));
  double c = double(b + 1524);
  double d = double(int((c-122.1)/365.25));
  double e = double(int(365.25*d));
  double g = double(int((c-e)/30.6001));
  int id = (int)(c-e-int(30.6001*g));
  int im = 0;
  if(g<13.5){im = (int)(g-1.);}
  else{ im = (int)(g-13.);}
  int iy=0;
  if(im>=3){ iy = (int)(d-4716.);}
  else{iy = (int)(d-4715.);}

  fYear = iy;
  fMonth = im;
  fDay = id;
  int sec = UTSecs;
  fHour = int(sec/3600);
  sec = sec - 3600*fHour;
  fMin = int(sec/60);
  sec = sec - 60*fMin;
  fSec = sec;
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
