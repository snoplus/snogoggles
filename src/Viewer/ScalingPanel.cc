#include <SFML/Window/Event.hpp>

using namespace std;

#include <Viewer/ScalingPanel.hh>
#include <Viewer/Event.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/AxisScaler.hh>
#include <Viewer/DataSelector.hh>
using namespace Viewer;

ScalingPanel::ScalingPanel( RectPtr rect,
                            RenderState& renderState )
  : Panel( rect, "ScalingPanel" ), fRenderState( renderState )
{

}

ScalingPanel::~ScalingPanel()
{

}

void
ScalingPanel::EventLoop()
{
  GUIProperties::GetInstance().Reset();
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case eScaling: // Change in scaling
          fRenderState.ChangeScaling( dynamic_cast<GUIs::AxisScaler*>( fGUIs[eScaling] )->GetMin(), 
                                      dynamic_cast<GUIs::AxisScaler*>( fGUIs[eScaling] )->GetMax() );
          break;
        }
      fEvents.pop();
    }
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();  
  dynamic_cast<GUIs::AxisScaler*>( fGUIs[eScaling] )->SetLimits( event.GetSource( fRenderState.GetDataSource() ).GetType( fRenderState.GetDataType() ).GetMin(),
                                                                 event.GetSource( fRenderState.GetDataSource() ).GetType( fRenderState.GetDataType() ).GetMax() );
}

void 
ScalingPanel::PreInitialise( const ConfigurationTable* configTable )
{
  Panel::PreInitialise( configTable );
  if( configTable != NULL )
    {

    }
}

void
ScalingPanel::PostInitialise( const ConfigurationTable* configTable )
{
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();  
  dynamic_cast<GUIs::AxisScaler*>( fGUIs[eScaling] )->SetLimits( event.GetSource( fRenderState.GetDataSource() ).GetType( fRenderState.GetDataType() ).GetMin(),
                                                                 event.GetSource( fRenderState.GetDataSource() ).GetType( fRenderState.GetDataType() ).GetMax() );
  dynamic_cast<GUIs::AxisScaler*>( fGUIs[eScaling] )->Reset();
}

void
ScalingPanel::LoadGUIConfiguration( const ConfigurationTable* config )
{
  for( unsigned int uGUIs = 0; uGUIs < config->GetNumTables(); uGUIs++ )
    {
      const ConfigurationTable* objectConfig = config->GetTable( uGUIs );
      if( objectConfig->GetName() == string( "gui" ) )
        {
          sf::Rect<double> posRect = LoadRect( objectConfig, fRect );
          switch( objectConfig->GetI( "effect" ) )
            {
            case eScaling:
              {
                fGUIs[eScaling] = fGUIManager.NewGUI<GUIs::AxisScaler>( posRect, objectConfig->GetI( "effect" ) );
                dynamic_cast<GUIs::AxisScaler*>( fGUIs[eScaling] )->Reset();
              }
              break;
            }
        }
    }
}

void
ScalingPanel::SaveConfiguration( ConfigurationTable* configTable )
{

}
