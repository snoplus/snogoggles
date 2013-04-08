#include <TVector3.h>

#include <Viewer/DefaultHits3d.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/RenderState.hh>
using namespace Viewer;
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/ChannelList.hh>

void 
DefaultHits3d::EventLoop()
{
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // Display all
          fDisplayAll = !fDisplayAll;
          break;
        case 1: // Display front
          fDisplayFront = !fDisplayFront;
          break;
        }
      fEvents.pop();
    }
}

void 
DefaultHits3d::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "DisplayAll", fDisplayAll );
  configTable->SetI( "DisplayFront", fDisplayFront );
}

void 
DefaultHits3d::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> size;
  size.left = 0.0;
  size.top = 0.0;
  size.width = 0.5;
  size.height = 1.0;
  GUIs::PersistLabel* displayAll = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  displayAll->Initialise( 16, "Display All" );
  size.left += 0.5;
  GUIs::PersistLabel* displayFront = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  displayFront->Initialise( 16, "Front Only" );
  if( configTable != NULL )
    {
      fDisplayAll = static_cast<bool>( configTable->GetI( "DisplayAll" ) );
      fDisplayFront = static_cast<bool>( configTable->GetI( "DisplayFront" ) );
    }
  displayAll->SetState( fDisplayAll );
  displayFront->SetState( fDisplayFront );
}

void
DefaultHits3d::ProcessData( const RenderState& renderState )
{
  fFullBuffer.Clear();
  fOutlineBuffer.Clear();

  const std::vector<RIDS::Channel>& hits = DataSelector::GetInstance().GetData( renderState.GetDataSource(), renderState.GetDataType() );
  const RIDS::ChannelList& channelList = DataSelector::GetInstance().GetChannelList();
  for( int i = 0; i < hits.size(); i++ )
    {
      if( hits[i].GetData() == 0 || hits[i].GetID() >= channelList.GetChannelCount() )
        continue;

      const sf::Vector3<double> pp = channelList.GetPosition( hits[i].GetID() );
      TVector3 p( pp.x, pp.y, pp.z );
      Colour c = renderState.GetDataColour( hits[i].GetData() );

      fFullBuffer.AddHitFull( p, c );
      fOutlineBuffer.AddHitOutline( p, c );
    }

  fFullBuffer.Bind();
  fOutlineBuffer.Bind();

  fPMTListBuffer.Clear();
  for( int i=0; i < channelList.GetChannelCount(); i++ )
    {
      const sf::Vector3<double> pp = channelList.GetPosition( i );
      TVector3 p( pp.x, pp.y, pp.z );
      if( p.Mag2() > 0.0 )
        fPMTListBuffer.AddHitOutline( p, GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGrey ) );
    }
  fPMTListBuffer.Bind();
}

void
DefaultHits3d::Render3d()
{
  if( !fDisplayFront )
    fOutlineBuffer.Render( GL_LINES );
  
  glEnable( GL_DEPTH_TEST );

  if( fDisplayAll )
    fPMTListBuffer.Render( GL_LINES );
  
  fFullBuffer.Render( GL_TRIANGLES );
  glDisable( GL_DEPTH_TEST );
}
