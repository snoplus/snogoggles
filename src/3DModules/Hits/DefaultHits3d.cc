#include <Viewer/DefaultHits3d.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RIDS/EV.hh>
#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/PMTHit.hh>
#include <Viewer/DataStore.hh>

#include <RAT/DS/PMTProperties.hh>
#include <RAT/DS/Run.hh>
#include <SFML/OpenGL.hpp>

#include <iostream>

namespace Viewer {
namespace Frames {

const std::string DefaultHits3d::fDisplayAllPMTsTag = "DisplayAllPMTs";
const std::string DefaultHits3d::fPMTTypeTag = "PMTType";
const std::string DefaultHits3d::fDisplayFrontPMTsOnlyTag = "DisplayFrontPMTsOnly";

DefaultHits3d::DefaultHits3d()
{
    fDisplayAllPMTs = false;
    fDisplayFrontPMTsOnly = false;
    fInitialised = false;
    fCurrentEV = NULL;
    fAllPMTsGUI = NULL;
    fFrontGUI = NULL;
}

void DefaultHits3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    sf::Rect<double> rect( optionsArea.left, optionsArea.top, optionsArea.width / 2.2, optionsArea.height); 
    fAllPMTsGUI = g.NewGUI<GUIs::PersistLabel>( rect );
    fAllPMTsGUI->SetLabel( "Display All PMTs" );
    fAllPMTsGUI->SetState( fDisplayAllPMTs );

    rect.left += optionsArea.width/2;
    fFrontGUI = g.NewGUI<GUIs::PersistLabel>( rect );
    fFrontGUI->SetLabel( "Show Front PMTs Only" );
    fFrontGUI->SetState( fDisplayFrontPMTsOnly );
}

void DefaultHits3d::LoadConfiguration( const ConfigurationTable* configTable )
{
    ConfigTableUtils::GetBooleanSafe( configTable, fDisplayAllPMTsTag, fDisplayAllPMTs );
    ConfigTableUtils::GetBooleanSafe( configTable, fDisplayFrontPMTsOnlyTag, fDisplayFrontPMTsOnly );
}

void DefaultHits3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, fDisplayAllPMTsTag, fDisplayAllPMTs );
    ConfigTableUtils::SetBoolean( configTable, fDisplayFrontPMTsOnlyTag, fDisplayFrontPMTsOnly );
}

void DefaultHits3d::EventLoop( )
{
    // TODO: Needs to be completed
    fDisplayAllPMTs = fAllPMTsGUI->GetState();
    fDisplayFrontPMTsOnly = fFrontGUI->GetState();
}

void DefaultHits3d::ProcessData( const RenderState& renderState )
{
    RIDS::EV& ev = DataStore::GetInstance().GetCurrentEvent().GetEV();
    RAT::DS::PMTProperties* pmtList = DataStore::GetInstance().GetRun().GetPMTProp();
    SaveHitsToBuffer( &ev, pmtList, renderState );
}

void DefaultHits3d::Render( const RenderState& renderState )
{
    if( fInitialised == false ) 
        ProcessData( renderState );
    fInitialised = true;

    RAT::DS::PMTProperties* pmtList = DataStore::GetInstance().GetRun().GetPMTProp();
    if( fCurrentPMTList != pmtList )
    {
        for( int i=0; i < pmtList->GetPMTCount(); i++ )
          fPMTListBuffer.AddHitOutline( pmtList->GetPos( i ), 
            GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGrey ) );
        fPMTListBuffer.Bind();
        fCurrentPMTList = pmtList;
    }

    if( !fDisplayFrontPMTsOnly )
        fOutlineBuffer.Render( GL_LINES );

    glEnable( GL_DEPTH_TEST );

    if( fDisplayAllPMTs )
        fPMTListBuffer.Render( GL_LINES );    

    fFullBuffer.Render( GL_TRIANGLES );
    glDisable( GL_DEPTH_TEST );
}

void DefaultHits3d::SaveHitsToBuffer( RIDS::EV* ev, RAT::DS::PMTProperties* pmtList, const RenderState& renderState )
{
    fFullBuffer.Clear();
    fOutlineBuffer.Clear();

    if( ev == NULL ) return;

    const std::vector<RIDS::PMTHit>& hits = DataStore::GetInstance().GetHitData( renderState.GetDataSource() );
    for( int i = 0; i < hits.size(); i++ )
    {
        if( hits[i].GetData( renderState.GetDataType() ) == 0 || i >= pmtList->GetPMTCount() )
            continue;

        TVector3 p = pmtList->GetPos( hits[i].GetLCN() );
        Colour c = renderState.GetHitColour( hits[i] );

        fFullBuffer.AddHitFull( p, c );
        fOutlineBuffer.AddHitOutline( p, c );
    }

    fFullBuffer.Bind();
    fOutlineBuffer.Bind();
}


}; // namespace Frames
}; // namespace Viewer
