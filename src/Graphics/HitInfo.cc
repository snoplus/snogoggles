#include <sstream>
using namespace std;

#include <Viewer/HitInfo.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/RIDS/RIDS.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/BitManip.hh>
#include <Viewer/PythonScripts.hh>
using namespace Viewer;

void
HitInfo::Render( RWWrapper& renderApp,
                 const RenderState& renderState,
                 const unsigned int lcn )
{
  stringstream end;
  if( fHorizontal )
    end << "    ";
  else
    end << " " << endl;
 
  stringstream info;
  info << "LCN:" << lcn << end.str();
  int crate = BitManip::GetBits(lcn, 9, 5);
  int card = BitManip::GetBits(lcn, 5, 4);
  int channel = BitManip::GetBits(lcn, 0, 5);
  info << "Cr:Cd:Ch:" << crate << ":" << card << ":" << channel << end.str();

  bool hasData = false;
  vector<RIDS::PMTHit> hits = DataStore::GetInstance().GetHitData( renderState.GetDataSource() );
  vector<string> dataTypes;
  if( renderState.GetDataSource() == RIDS::eScript )
    dataTypes = PythonScripts::GetInstance().GetAnalysis().GetDataLabels();
  else
    dataTypes = RenderState::GetTypeStrings();
  for( vector<RIDS::PMTHit>::iterator iTer = hits.begin(); iTer != hits.end(); iTer++ )
    {
      if( lcn == iTer->GetLCN() )
        {
          info << dataTypes[0] << ":" << iTer->GetTAC() << end.str();
          info << dataTypes[1] << ":" << iTer->GetQHL() << end.str();
          info << dataTypes[2] << ":" << iTer->GetQHS() << end.str();
          info << dataTypes[3] << ":" << iTer->GetQLX() << end.str();
          hasData = true;
        }
    }
  if( hasData )
    {
      fInfoText.SetString( info.str() );
      fInfoText.SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      renderApp.Draw( fInfoText );
    }
}
