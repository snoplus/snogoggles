#include <RAT/DS/MC.hh>

#include <vector>
#include <iostream>
using namespace std;

#include <Viewer/RIDS/MC.hh>
using namespace Viewer::RIDS;

MC::MC( RAT::DS::MC& rMC )
{
  for( int i = 0; i < rMC.GetMCTrackCount(); i++ )
    fTracks.push_back( Track( *rMC.GetMCTrack( i ) ) );
}

MC::~MC()
{
  
}

vector<PMTHit>
MC::GetData( EDataSource source )
{
  return fHits;
}
