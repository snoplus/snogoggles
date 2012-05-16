#include <sstream>
using namespace std;

#include <Viewer/HitInfo.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/GUIColourPalette.hh>
#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/PMTHit.hh>
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
  DataStore& events = DataStore::GetInstance();
  const RIDS::Event& event = events.GetCurrentEvent();

  bool hasData = false;
  vector<RIDS::PMTHit> hits = event.GetHitData( renderState.GetDataSource() );
  for( vector<RIDS::PMTHit>::iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      if( pmtID == iTer->GetLCN() )
        {
          info << "TAC:" << iTer->GetTAC() << end.str();
          info << "QHL:" << iTer->GetQHL() << end.str();
          info << "QHS:" << iTer->GetQHS() << end.str();
          info << "QLX:" << iTer->GetQLX() << end.str();
          hasData = true;
        }
    }
  if( hasData )
    {
      fInfoText.SetString( info.str() );
      fInfoText.SetColour( GUIColourPalette::gPalette->GetTextColour( eBase ) );
      renderApp.Draw( fInfoText );
    }
}
