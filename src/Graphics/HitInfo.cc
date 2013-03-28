#include <sstream>
using namespace std;

#include <Viewer/HitInfo.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/DataStore.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/BitManip.hh>
#include <Viewer/PythonScripts.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>

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
  const RIDS::Source& sourceData = DataStore::GetInstance().GetCurrentEvent().GetSource( renderState.GetDataSource() );
  vector<string> dataTypes;
  if( renderState.GetDataSource() < 0 ) // Negative sources are scripts
    dataTypes = PythonScripts::GetInstance().GetAnalysis().GetTypeNames();
  else
    dataTypes = RIDS::Event::GetTypeNames( renderState.GetDataSource() );
  for( size_t iChannel = 0; iChannel < sourceData.GetCount(); iChannel++ )
    {
      if( lcn == sourceData.GetType( 0 ).GetChannel( iChannel ).GetID() )
        {
          for( size_t iType = 0; iType < dataTypes.size(); iType++ )
            {
              info << dataTypes[iType] << ":" << sourceData.GetType( iType ).GetChannel( iChannel ).GetData() << end.str();
              hasData = true;
            }
        }
    }
  if( hasData )
    {
      fInfoText.SetString( info.str() );
      fInfoText.SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
      renderApp.Draw( fInfoText );
    }
}
