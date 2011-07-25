#include <RAT/DS/MCTrack.hh>
#include <RAT/DS/MCTrackStep.hh>
#include <SFML/OpenGL.hpp>

#include <Viewer/SerializableFactory.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/LineStrip.hh>

#include <iostream>

namespace Viewer {

LineStrip::LineStrip( RAT::DS::MCTrack* tr )
{
    for( int i = 0; i < tr->GetMCTrackStepCount(); i++ )
        AddVector3( Vector3( tr->GetMCTrackStep(i)->GetEndPos() ) );
}

void LineStrip::RenderFull() const
{
    glBegin( GL_LINE_STRIP );

    if( fVisAttributes->IsVisible() == true )
    {
        glPushAttrib( GL_COLOR );
        fVisAttributes->SetOpenGLColour();

        for( int i = 0; i < fVertices.size(); i++ )
            fVertices.at(i).Render();

        glPopAttrib();
    }

    glEnd();
}

void LineStrip::RenderSymbolic() const
{
    glBegin( GL_LINES );
    if( fVisAttributes->IsVisible() == true )
    {
        glPushAttrib( GL_COLOR );
        fVisAttributes->SetOpenGLColour();

        fVertices.front().Render();
        fVertices.back().Render();

        glPopAttrib();
    }
    glEnd();
}

void LineStrip::Load( ConfigurationTable* configTable )
{
    std::vector< Vector3 > vertices;
    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string name = "vertex" + stream.str();
        try { vertices.push_back( SerializableFactory::GetInstance()->New< Vector3 >( configTable, name ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    fVertices = vertices;
}

void LineStrip::Save( ConfigurationTable* configTable ) const
{
    for( int i = 0; i < fVertices.size(); i++ )
    {
        std::stringstream stream; stream << i;
        std::string name = "vertex" + stream.str();
        fVertices.at(i).SaveToParentTable( configTable, name );
    }
}

}; // namespace Viewer
