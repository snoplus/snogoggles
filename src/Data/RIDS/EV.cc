#include <RAT/DS/EV.hh>

#include <vector>
using namespace std;

#include <Viewer/RIDS/EV.hh>
using namespace Viewer::RIDS;

EV::EV( RAT::DS::EV& rEV )
{
  fClock50 = rEV.GetClockCount50();
  fClock10 = rEV.GetClockCount10();
  fTriggerWord = rEV.GetTrigType();
  fGTID = rEV.GetEventID();
  for( unsigned int ipmt = 0; ipmt < rEV.GetPMTAllTruthCount(); ipmt++ )
    fTruthHits.push_back( PMTHit( rEV.GetPMTAllTruth( ipmt ) ) );
  for( unsigned int ipmt = 0; ipmt < rEV.GetPMTAllUnCalCount(); ipmt++ )
    fUnCalHits.push_back( PMTHit( rEV.GetPMTAllUnCal( ipmt ) ) );
  for( unsigned int ipmt = 0; ipmt < rEV.GetPMTAllCalCount(); ipmt++ )
    fCalHits.push_back( PMTHit( rEV.GetPMTAllCal( ipmt ) ) );
  fTime = Time( fClock10 );
}

EV::~EV()
{
  
}

vector<PMTHit>
EV::GetHitData( EDataSource source ) const
{
  switch( source )
    {
    case eMC:
    case eScript:
      // This should not happen....
      break;
    case eTruth:
      return fTruthHits;
    case eUnCal:
      return fUnCalHits;
    case eCal:
      return fCalHits;
    }
  // Return empty vector if get here...
  return vector<PMTHit>();
}
