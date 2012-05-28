#include <iostream>
#include <Viewer/RIDS/MC.hh>
#include <Viewer/RIDS/Track.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/TrackBuffer.hh>

namespace Viewer {

void TrackBuffer::AddParticleType( const std::string& name, float colour )
{
    struct ParticleType p;
    p.fColour = colour;
    p.fVisible = true;
    fParticleTypes[ name ] = p;
}

std::vector< std::string > TrackBuffer::GetNames()
{
    std::vector< std::string > names;
    std::map< std::string, struct ParticleType >::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++) 
        names.push_back( itr->first );
    return names;
}

void TrackBuffer::LoadVisibility( const ConfigurationTable* configTable )
{
    std::map< std::string, struct ParticleType >::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++)
        ConfigTableUtils::GetBooleanSafe( configTable, itr->first, itr->second.fVisible );
}

void TrackBuffer::SaveVisibility( ConfigurationTable* configTable )
{
    std::map< std::string, struct ParticleType >::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++)
        ConfigTableUtils::SetBoolean( configTable, itr->first, itr->second.fVisible );
}

void TrackBuffer::SetAll( RIDS::MC& mc )
{
    ClearAll();

    std::vector< RIDS::Track >& tracks = mc.GetTracks();
    for( int i = 0; i < tracks.size(); i++ )
    {
        const std::string& name = tracks[i].GetParticleName();
        struct ParticleType& pt = fParticleTypes[ name ];
        const Colour& c = GUIProperties::GetInstance().GetColourPalette().GetColour( pt.fColour );
        const std::vector< RIDS::TrackStep >& trackSteps = tracks[i].GetTrackSteps();
        
        AddLine( pt.fSimpleVBO, trackSteps[0].GetEndPos(), trackSteps[ trackSteps.size() - 1 ].GetEndPos(), c );

        for( int i = 0; i < trackSteps.size() - 1; i++ )
            AddLine( pt.fAllStepsVBO, trackSteps[i].GetEndPos(), trackSteps[i+1].GetEndPos(), c );
    }

    BindAll();
}

void TrackBuffer::Render( bool renderAllSteps )
{
    std::map< std::string, struct ParticleType >::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++) 
    {
        if( itr->second.fVisible )
        {
            if( renderAllSteps )
                itr->second.fAllStepsVBO.Render( GL_LINES );
            else
                itr->second.fSimpleVBO.Render( GL_LINES );
        }            
    }   
}

void TrackBuffer::ClearAll()
{
    std::map< std::string, struct ParticleType >::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++) 
    {
        itr->second.fSimpleVBO.Clear();
        itr->second.fAllStepsVBO.Clear();
    }
}

void TrackBuffer::BindAll()
{
    std::map< std::string, struct ParticleType >::iterator itr;
    for( itr = fParticleTypes.begin(); itr != fParticleTypes.end(); itr++) 
    {
        itr->second.fSimpleVBO.Bind();
        itr->second.fAllStepsVBO.Bind();
    }
}

void TrackBuffer::AddLine( VBO& vbo, const TVector3& startPos, const TVector3& endPos, const Colour& colour )
{
        unsigned short i = vbo.fVertices.size();
        vbo.AddVertex( Vertex( startPos, colour ) );
        vbo.AddVertex( Vertex( endPos, colour ) );
        vbo.AddIndex(i);
        vbo.AddIndex(i+1);
}

}; // namespace Viewer 
