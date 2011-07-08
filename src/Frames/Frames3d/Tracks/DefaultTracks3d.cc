#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/GUIManager.hh>
#include <Viewer/GUIReturn.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/ConfigTableUtils.hh>

#include <RAT/DS/MC.hh>
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <string>

namespace Viewer {
namespace Frames {

sf::Color DefaultTracks3d::fUnkownParticleColour( 105, 105, 105 );

DefaultTracks3d::DefaultTracks3d()
{
    fReFilter = false;
    fAllParticles = false;
    fRenderFullTrack = false;

    AddParticleType( "opticalphoton", sf::Color::Red );
    AddParticleType( "gamma", sf::Color::Green );
    AddParticleType( "e-", sf::Color::Blue );
    AddParticleType( "neutron", sf::Color::Yellow );
    AddParticleType( "neutrino", sf::Color::Magenta );
}

void DefaultTracks3d::CreateGUIObjects( GUIManager* g, const sf::Rect<double>& optionsArea )
{
    // TODO:
}

void DefaultTracks3d::LoadConfiguration( ConfigurationTable* configTable )
{
    fRenderFullTrack = ConfigTableUtils::GetBoolean( configTable, RenderFullTrackTag() );
    fAllParticles = ConfigTableUtils::GetBoolean( configTable, AllParticlesTag() );

    std::map<std::string, ParticleType>::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++ )
    {
        std::string name = itr->first;
        fParticleTypes[ name ].fDisplay = ConfigTableUtils::GetBoolean( configTable, name );
    }
}

void DefaultTracks3d::SaveConfiguration( ConfigurationTable* configTable )
{
    ConfigTableUtils::SetBoolean( configTable, RenderFullTrackTag(), fRenderFullTrack );
    ConfigTableUtils::SetBoolean( configTable, AllParticlesTag(), fAllParticles );

    std::map<std::string, ParticleType>::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++ )
    {
        std::string name = itr->first;
        ConfigTableUtils::SetBoolean( configTable, name, fParticleTypes[ name ].fDisplay );
    }
}

void DefaultTracks3d::EventLoop( const GUIReturn& g )
{
    // TODO:
}

void DefaultTracks3d::RenderTracks( RAT::DS::MC* mc )
{
    if( fCurrentMC != mc || fReFilter == true )
    {
        fCurrentMC = mc;
        FilterTracks( fCurrentMC );
    }

    for( int i=0; i < fFilteredTracks.size(); i++)
    {
        if( fRenderFullTrack == true )
            RenderFullTrack( fFilteredTracks.at(i) );
        else
            RenderSymbolicTrack( fFilteredTracks.at(i) );
    }
}

void DefaultTracks3d::FilterTracks( RAT::DS::MC* mc )
{
    fFilteredTracks.clear();
    for( int i=0; i < mc->GetMCTrackCount(); i++)
    {
        FilterByPrimaryTrack( mc->GetMCTrack( i ) );
    }
}

void DefaultTracks3d::FilterByPrimaryTrack( RAT::DS::MCTrack* tr )
{
    if( tr->GetParentID() == 0 )
        FilterByParticleType( tr );
}

void DefaultTracks3d::FilterByParticleType( RAT::DS::MCTrack* tr )
{
    if( fParticleTypes.count( tr->GetParticleName() ) == 0 )
    {
        if( fAllParticles == true )
            AddToFilteredTracks( Track( tr, &fUnkownParticleColour ) );
    }
    else 
    {
        ParticleType& pt = fParticleTypes[ tr->GetParticleName() ]; 
        if( pt.fDisplay == true || fAllParticles == true )
        {
            AddToFilteredTracks( Track( tr, &(pt.fColour) ) );
        }
    }
}

}; // namespace Frames
}; // namespace Viewer
