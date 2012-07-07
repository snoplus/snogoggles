#include <Viewer/DefaultHits3d.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/RIDS/EV.hh>
#include <Viewer/RIDS/PMTHit.hh>

#include <RAT/DS/PMTProperties.hh>
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
    sf::Rect<double> rect( optionsArea.Left, optionsArea.Top, optionsArea.Width / 2.2, optionsArea.Height); 
    fAllPMTsGUI = g.NewGUI<GUIs::PersistLabel>( rect );
    fAllPMTsGUI->SetLabel( "Display All PMTs" );
    fAllPMTsGUI->SetState( fDisplayAllPMTs );

    rect.Left += optionsArea.Width/2;
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

void DefaultHits3d::RenderHits( RIDS::EV* ev, RAT::DS::PMTProperties* pmtList, const RenderState& renderState )
{
    if( StateChanged( renderState ) || fInitialised == false ) 
        SaveHitsToBuffer( ev, pmtList, renderState );
    fInitialised = true;

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

    std::vector<RIDS::PMTHit> hits = ev->GetHitData( renderState.GetDataSource() );
    for( int i = 0; i < hits.size(); i++ )
    {
        TVector3 p = pmtList->GetPos( hits[i].GetLCN() );

        double max = renderState.GetScalingMax();
        double min = renderState.GetScalingMin();
        double data = hits[i].GetData( renderState.GetDataType() );
        double c_frac = data / ( max - min );

        Colour c = GUIProperties::GetInstance().GetColourPalette().GetColour( c_frac );

        fFullBuffer.AddHitFull( p, c );
        fOutlineBuffer.AddHitOutline( p, c );
    }

    fFullBuffer.Bind();
    fOutlineBuffer.Bind();
}


}; // namespace Frames
}; // namespace Viewer
