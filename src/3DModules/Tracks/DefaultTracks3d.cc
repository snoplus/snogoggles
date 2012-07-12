#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/RIDS/MC.hh>
#include <Viewer/DataStore.hh>

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
    fRenderFullTrack = true;
    fInitialised = false;
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

    fFullTrackGUI = g.NewGUI<GUIs::PersistLabel>( rect );
    fFullTrackGUI->SetLabel( "Render All Track Steps" );

    for( int i = 0; i < names.size(); i++ )
    {
        rect.Top += optionsArea.Height / numGUIs;
        fGUIs[ names.at(i) ] = g.NewGUI< GUIs::PersistLabel >( rect );
        fGUIs[ names.at(i) ]->SetLabel( names.at(i) );
        fGUIs[ names.at(i) ]->SetState( fTrackBuffer.fParticleTypes[ names.at(i) ].fVisible );
    }
}

void DefaultTracks3d::LoadConfiguration( const ConfigurationTable* configTable )
{
    ConfigTableUtils::GetBooleanSafe( configTable, RENDER_FULL_TRACK, fRenderFullTrack );
    try{ fTrackBuffer.LoadVisibility( configTable ); }
    catch( ConfigurationTable::NoAttributeError& e ) { }
}

void DefaultTracks3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, RENDER_FULL_TRACK, fRenderFullTrack );
    fTrackBuffer.SaveVisibility( configTable );
}

void DefaultTracks3d::EventLoop( )
{
    if( fFullTrackGUI != NULL )
        if( fFullTrackGUI->GetState() != fRenderFullTrack )
            fRenderFullTrack = fFullTrackGUI->GetState();

    if( fGUIs.empty() == false )
    {
        std::map< std::string, GUIs::PersistLabel* >::iterator itr;
        for( itr = fGUIs.begin(); itr != fGUIs.end(); itr++ )
            fTrackBuffer.fParticleTypes[ itr->first ].fVisible = fGUIs[ itr->first ]->GetState();
    }
}

void DefaultTracks3d::ProcessData( const RenderState& renderState )
{
    RIDS::MC& mc = DataStore::GetInstance().GetCurrentEvent().GetMC();
    fTrackBuffer.SetAll( mc );
}

void DefaultTracks3d::Render( const RenderState& renderState )
{
    if( fInitialised == false )
        ProcessData( renderState );
    fInitialised = true;

    fTrackBuffer.Render( fRenderFullTrack );
}

void DefaultTracks3d::AddParticleType( const std::string& name, float eColour )
{
    fTrackBuffer.AddParticleType( name, eColour );
}

}; // namespace Frames
}; // namespace Viewer
