#include <RAT/DS/PMTCal.hh>
#include <RAT/DS/PMTUnCal.hh>
#include <RAT/DS/PMTTruth.hh>
#include <RAT/DS/MCPMT.hh>

#include <Viewer/RIDS/PMTHit.hh>
using namespace Viewer::RIDS;

PMTHit::PMTHit( RAT::DS::PMTCal* rPMTCal )
{
  fLCN = rPMTCal->GetID();
  fTAC = rPMTCal->GetsPMTt();
  fQHL = rPMTCal->GetsQHL();
  fQHS = rPMTCal->GetsQHS();
  fQLX = rPMTCal->GetsQLX();
}

PMTHit::PMTHit( RAT::DS::PMTUnCal* rPMTUnCal )
{
  fLCN = rPMTUnCal->GetID();
  fTAC = rPMTUnCal->GetsPMTt();
  fQHL = rPMTUnCal->GetsQHL();
  fQHS = rPMTUnCal->GetsQHS();
  fQLX = rPMTUnCal->GetsQLX();
}

PMTHit::PMTHit( RAT::DS::PMTTruth* rPMTTruth )
{
  fLCN = rPMTTruth->GetID();
  fTAC = rPMTTruth->GetsPMTt();
  fQHL = rPMTTruth->GetsQHL();
  fQHS = rPMTTruth->GetsQHS();
  fQLX = rPMTTruth->GetsQLX();
}

PMTHit::PMTHit( RAT::DS::MCPMT* rMCPMT )
{
  
}

double
PMTHit::GetData( EDataType type )
{
  switch( type )
    {
    case eTAC:
      return fTAC;
    case eQHL:
      return fQHL;
    case eQHS:
      return fQHS;
    case eQLX:
      return fQLX;
    }
  return 0.0;
}

PMTHit::~PMTHit()
{

}
