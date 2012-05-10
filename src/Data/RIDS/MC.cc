#include <RAT/DS/MC.hh>

#include <vector>
using namespace std;

#include <Viewer/RIDS/MC.hh>
using namespace Viewer::RIDS;

MC::MC( RAT::DS::MC& rMC )
{

}

MC::~MC()
{
  
}

vector<PMTHit>
MC::GetData( EDataSource source )
{
  return fHits;
}
