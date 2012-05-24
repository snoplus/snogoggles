#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ColourPalette.hh>
#include <Viewer/CheckBoxLabel.hh>

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
	fFullTrackGUI = NULL;

    AddParticleType( "opticalphoton", 0 );
    AddParticleType( "gamma", 1.f/6 );
    AddParticleType( "e-", 2.f/6 );
    AddParticleType( "neutrino", 3.f/6 );
    AddParticleType( "neutron", 4.f/6 );
    AddParticleType( "unknown", 5.f/6 );
}

void DefaultTracks3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    std::vector< std::string > names = fTrackBuffer.GetNames();
    int numGUIs = names.size() + 1;
    sf::Rect<double> rect( optionsArea.Left, optionsArea.Top, optionsArea.Width, optionsArea.Width / 5);

    fFullTrackGUI = g.NewGUI<GUIs::CheckBoxLabel>( rect );
    fFullTrackGUI->SetLabel( "Render All Track Steps" );

    for( int i = 0; i < names.size(); i++ )
    {
        rect.Top += optionsArea.Height / numGUIs;
        fGUIs[ names.at(i) ] = g.NewGUI< GUIs::CheckBoxLabel >( rect );
        fGUIs[ names.at(i) ]->SetLabel( names.at(i) );
        fGUIs[ names.at(i) ]->SetState( fTrackBuffer.fParticleTypes[ names.at(i) ].fVisible );
    }
}

void DefaultTracks3d::LoadConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::GetBooleanSafe( configTable, RENDER_FULL_TRACK, fRenderFullTrack );
    ConfigTableUtils::GetBooleanSafe( configTable, PRIMARY_TRACKS_ONLY, fPrimaryTracksOnly );
    try{ fTrackBuffer.LoadVisibility( configTable ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void DefaultTracks3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, RENDER_FULL_TRACK, fRenderFullTrack );
    ConfigTableUtils::SetBoolean( configTable, PRIMARY_TRACKS_ONLY, fPrimaryTracksOnly );
    fTrackBuffer.SaveVisibility( configTable );
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
            fTrackBuffer.fParticleTypes[ itr->first ].fVisible = fGUIs[ itr->first ]->GetState();
    }
}

void DefaultTracks3d::RenderTracks( RIDS::MC& mc )
{
    fTrackBuffer.SetAll( mc );
    fTrackBuffer.Render( fRenderFullTrack );
}

void DefaultTracks3d::AddParticleType( const std::string& name, float eColour )
{
    fTrackBuffer.AddParticleType( name, ColourPalette::gPalette->GetColour( eColour ) );
}

}; // namespace Frames
}; // namespace Viewer
