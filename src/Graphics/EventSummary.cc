#include <sstream>
using namespace std;

#include <Viewer/EventSummary.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RWWrapper.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/BitManip.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>

void
EventSummary::Render( RWWrapper& renderApp,
                      const RenderState& renderState )
{
  stringstream eventInfo;
  eventInfo.precision( 0 );
  eventInfo << fixed;

  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  eventInfo << "Run :" << event.GetRunID() << " ";
  eventInfo << "Sub Run :" << event.GetSubRunID() << " ";
  eventInfo << "Event GTID :" << event.GetEventID() << " ";
  //eventInfo << "Trigger :" << TriggerToString( event.GetTrigger() ) << " ";

  const vector<string> sourceNames = RIDS::Event::GetSourceNames();
  eventInfo << "Source :" << sourceNames[renderState.GetDataSource()] << " ";
  const vector<string> typeNames = RIDS::Event::GetTypeNames( renderState.GetDataSource() );
  eventInfo << "Type :" << typeNames[ renderState.GetDataType() ];
  
  fInfoText.SetString( eventInfo.str() );
  fInfoText.SetColour( GUIProperties::GetInstance().GetGUIColourPalette().GetText() );
  renderApp.Draw( fInfoText );
}
