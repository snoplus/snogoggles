#include <RAT/DB.hh>
#include <RAT/Log.hh>

#include <string>
using namespace std;

#include <Viewer/RIDS/ChannelList.hh>
using namespace Viewer::RIDS;

void 
ChannelList::Initialise( int /*runID*/ ) /// < Run ID defines which pmt info table to use
{
  RAT::Log::Init("/dev/null");

  RAT::DB* db = RAT::DB::Get();
  assert(db);

  string data = getenv("GLG4DATA");
  assert(data != "");
  db->Load(data + "/pmt/airfill2.ratdb");

  RAT::DBLinkPtr pmtInfo = db->GetLink("PMTINFO");
  assert(pmtInfo);

  vector<double> xPos = pmtInfo->GetDArray("x");
  vector<double> yPos = pmtInfo->GetDArray("y");
  vector<double> zPos = pmtInfo->GetDArray("z");
  for( size_t iPos = 0; iPos < xPos.size(); iPos++ )
    fPositions.push_back( sf::Vector3<double>( xPos[iPos], yPos[iPos], zPos[iPos] ) );
}
