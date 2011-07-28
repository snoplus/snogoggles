#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/CheckBoxLabel.hh>

#include <RAT/DS/MC.hh>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/OpenGL.hpp>

#include <map>
#include <vector>
#include <string>

namespace Viewer {
namespace Frames {

const std::string DefaultTracks3d::PRIMARY_TRACKS_ONLY = "primaryTracksOnly";
const std::string DefaultTracks3d::RENDER_FULL_TRACK = "renderFullTrack";
const std::string DefaultTracks3d::VIS_MAP = "particleTypes";

DefaultTracks3d::DefaultTracks3d()
{
    fAllParticles = true;
    fPrimaryTracksOnly = false;
    fRenderFullTrack = false;
    fRefilter = false;
    fCurrentMC = NULL;

    AddParticleType( "opticalphoton", eRed );
    AddParticleType( "gamma", eYellow );
    AddParticleType( "e-", eGreen );
    AddParticleType( "neutrino", eBlue );
    AddParticleType( "neutron", eIndigo );
    AddParticleType( "unknown", eGrey );
}

void DefaultTracks3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    std::vector< std::string > names = fVisMap.GetNames();
    int numGUIs = names.size() + 1;
    sf::Rect<double> rect( optionsArea.Left, optionsArea.Top, optionsArea.Width, optionsArea.Width);

    fFullTrackGUI = g.NewGUI<GUIs::CheckBoxLabel>( rect );
    fFullTrackGUI->SetLabel( "Render All Track Steps" );

    for( int i = 0; i < names.size(); i++ )
    {
        rect.Top += optionsArea.Height / numGUIs;
        fGUIs[ names.at(i) ] = g.NewGUI< GUIs::CheckBoxLabel >( rect );
        fGUIs[ names.at(i) ]->SetLabel( names.at(i) );
        fGUIs[ names.at(i) ]->SetState( fVisMap.IsVisible( names.at(i) ) );
    }
}

void DefaultTracks3d::LoadConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::GetBooleanSafe( configTable, RENDER_FULL_TRACK, fRenderFullTrack );
    ConfigTableUtils::GetBooleanSafe( configTable, PRIMARY_TRACKS_ONLY, fPrimaryTracksOnly );
    try{ fVisMap.LoadVisibility( configTable ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void DefaultTracks3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, RENDER_FULL_TRACK, fRenderFullTrack );
    ConfigTableUtils::SetBoolean( configTable, PRIMARY_TRACKS_ONLY, fPrimaryTracksOnly );
    fVisMap.SaveVisibility( configTable );
}

void DefaultTracks3d::EventLoop( )
{
    if( fFullTrackGUI != NULL )
        if( fFullTrackGUI->GetState() != fRenderFullTrack )
            fRenderFullTrack = fFullTrackGUI->GetState();

    if( fGUIs.empty() == false )
    {
        std::map< std::string, GUIs::CheckBoxLabel* >::iterator itr;
        for( itr = fGUIs.begin(); itr != fGUIs.end(); itr++ )
            if( fVisMap.IsVisible( itr->first ) != itr->second->GetState() )
            {
                fVisMap.SetVisibility( itr->first, itr->second->GetState() );
                fRefilter = true;
            }
    }
}

void DefaultTracks3d::RenderTracks( RAT::DS::MC* mc )
{
    if( fCurrentMC != mc || fRefilter == true )
    {
        fCurrentMC = mc;
        fRefilter = false;
        fLineStrips.clear();
        for( int i = 0; i < mc->GetMCTrackCount(); i++ )
        {
            RAT::DS::MCTrack* tr = mc->GetMCTrack( i );
            if( FilterByPrimaryTrack( tr ) && FilterByParticleType( tr ) )
            {
                LineStrip lineStrip( tr );

                if( fVisMap.Count( tr->GetParticleName() ) == 0 )
                    lineStrip.SetVisAttributes( fVisMap.GetVisAttributes( "unknown" ) );
                else
                    lineStrip.SetVisAttributes( fVisMap.GetVisAttributes( tr->GetParticleName() ) );

                fLineStrips.push_back( lineStrip );
            }
        }
    }

    for( int i = 0; i < fLineStrips.size(); i++ )
    {
        if( fRenderFullTrack == true )
            fLineStrips.at(i).RenderFull();
        else
            fLineStrips.at(i).RenderSymbolic();
    }
}

bool DefaultTracks3d::FilterByPrimaryTrack( RAT::DS::MCTrack* tr )
{
    if( fPrimaryTracksOnly == true )
        if( tr->GetParentID() != 0 )
            return false;

    return true;
}

bool DefaultTracks3d::FilterByParticleType( RAT::DS::MCTrack* tr )
{
    return fVisMap.IsVisible( tr->GetParticleName() );
}

void DefaultTracks3d::AddParticleType( const std::string& name, int eColour )
{
    fVisMap.AddVisAttributes( name, VisAttributes( ColourPalette::gPalette->GetPrimaryColour( static_cast< EColour >(eColour) ), true ) );
}

}; // namespace Frames
}; // namespace Viewer
