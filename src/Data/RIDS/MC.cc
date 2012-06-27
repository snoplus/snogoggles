#include <RAT/DS/MC.hh>

#include <vector>
#include <iostream>
using namespace std;

#include <Viewer/RIDS/MC.hh>
using namespace Viewer::RIDS;

MC::MC( RAT::DS::MC& rMC )
{
  for( unsigned int ipmt = 0; ipmt < rMC.GetMCPMTCount(); ipmt++ )
    {
      RAT::DS::MCPMT* rPMT = rMC.GetMCPMT( ipmt );
      for( unsigned int iPhoton = 0; iPhoton < 1/*rPMT->GetMCPhotonCount()*/; iPhoton++ ) // Snogoggles can't understand multiple hits on one pmt
        fHits.push_back( PMTHit( rPMT->GetMCPhoton( iPhoton ), rPMT->GetPMTID() ) );
    }

  for( int i = 0; i < rMC.GetMCTrackCount(); i++ )
    fTracks.push_back( Track( *rMC.GetMCTrack( i ) ) );
}

MC::~MC()
{
  
}

vector<PMTHit>
MC::GetHitData()
{
  return fHits;
}
