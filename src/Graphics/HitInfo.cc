#include <sstream>
using namespace std;

#include <Viewer/HitInfo.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/EventData.hh>
#include <Viewer/GUIColourPalette.hh>
using namespace Viewer;

void
HitInfo::Render( RWWrapper& renderApp,
		 const RenderState& renderState,
		 const unsigned int pmtID )
{
  stringstream end;
  if( fHorizontal )
    end << " ";
  else
    end << " " << endl;
 
  stringstream info;
  info << "LCN:" << pmtID << end.str();
  EventData& events = EventData::GetInstance();
  RAT::DS::EV* rEV = events.GetCurrentEV();

  bool hasData = false;
  switch( renderState.GetDataSource() )
    {
    case RenderState::eUnCal:
      {
	for( unsigned int ipmt = 0; ipmt < rEV->GetPMTUnCalCount(); ipmt++ )
	  {
	    RAT::DS::PMTUnCal* rPMTUnCal = rEV->GetPMTUnCal( ipmt );
	    if( rPMTUnCal->GetID() == pmtID )
	      {
		info << "TAC:" << rPMTUnCal->GetsPMTt() << end.str();
		info << "QHL:" << rPMTUnCal->GetsQHL() << end.str();
		info << "QHS:" << rPMTUnCal->GetsQHS() << end.str();
		info << "QLX:" << rPMTUnCal->GetsQLX() << end.str();
		hasData = true;
	      }
	  }
      }
      break;
    case RenderState::eCal:
      {
        for( unsigned int ipmt = 0; ipmt < rEV->GetPMTCalCount(); ipmt++ )
          {
	    RAT::DS::PMTCal* rPMTCal = rEV->GetPMTCal( ipmt );
            if( rPMTCal->GetID() == pmtID )
              {
                info << "TAC:" << rPMTCal->GetsPMTt() << end.str();
                info << "QHL:" << rPMTCal->GetsQHL() << end.str();
                info << "QHS:" << rPMTCal->GetsQHS() << end.str();
                info << "QLX:" << rPMTCal->GetsQLX() << end.str();
		hasData = true;
              }
          }
      }
      break;
    }
  if( hasData )
    {
      fInfoText.SetString( info.str() );
      fInfoText.SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
      renderApp.Draw( fInfoText );
    }
}
