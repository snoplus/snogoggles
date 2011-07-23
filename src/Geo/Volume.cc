#include <sstream>

#include <SFML/OpenGL.hpp>

#include <Viewer/Volume.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/SerializableFactory.hh>

namespace Viewer {

Volume::Volume(
    const std::string& name,
    const Vector3& translation,
    const Vector3& rotationAxis,
    double rotationAngle,
    const Polyhedron& polyhedron
)
{
    SetAll( name, translation, rotationAxis, rotationAngle, polyhedron );
}

void Volume::Render() const
{
    glPushMatrix();
    glTranslatef( fTranslation.x(), fTranslation.y(), fTranslation.z() );
    // TODO: Fix volume rotations!!!!!!!!!
    glRotatef( fRotationAngle, fRotationAxis.x(), fRotationAxis.y(), fRotationAxis.z() );

    if( fVisAttributes->IsVisible() == true )
    {
        glPushAttrib( GL_COLOR );
        fVisAttributes->SetOpenGLColour();
        fPolyhedron.Render();
        glPopAttrib();
    }

    for( int i = 0; i < fDaughterVolumes.size(); i++ )
        fDaughterVolumes.at(i).Render();

    glPopMatrix();
}

void Volume::Load( ConfigurationTable* configTable )
{
    SerializableFactory* s = SerializableFactory::GetInstance();
    std::string name = configTable->GetS( "name" );
    Vector3 translation = s->New< Vector3 >( configTable, "translation" );
    Vector3 rotationAxis = s->New< Vector3 >( configTable, "rotationAxis" );
    double rotationAngle = configTable->GetD( "rotationAngle" );
    Polyhedron polyhedron = s->New< Polyhedron >( configTable, "polyhedron" );

    std::vector< Volume > daughters;
    int i = 0;
    while( true )
    {
        std::stringstream stream; stream << i;
        std::string n = "volume" + stream.str();
        try{ daughters.push_back( s->New< Volume >( configTable, n ) ); }
        catch( ConfigurationTable::NoTableError& e ) { break; }
        i++;
    }

    SetAll( name, translation, rotationAxis, rotationAngle, polyhedron );
    fDaughterVolumes = daughters;
}

void Volume::Save( ConfigurationTable* configTable ) const
{
    configTable->SetS( "name", fName );
    fTranslation.SaveToParentTable( configTable, "translation" );
    fRotationAxis.SaveToParentTable( configTable, "rotationAxis" );
    configTable->SetD( "rotationAngle", fRotationAngle );
    fPolyhedron.SaveToParentTable( configTable, "polyhedron" );

    for( int i = 0; i < fDaughterVolumes.size(); i++ )
    {
        std::stringstream stream; stream << i;
        std::string n = "volume" + stream.str();
        fDaughterVolumes.at(i).SaveToParentTable( configTable, n );
    }
}

void Volume::SetAll(
    const std::string& name,
    const Vector3& translation,
    const Vector3& rotationAxis,
    double rotationAngle,
    const Polyhedron& polyhedron
)
{
    fName = name;
    fTranslation = translation;
    fRotationAxis = rotationAxis;
    fRotationAngle = rotationAngle;
    fPolyhedron = polyhedron;
}

}; // namespace Viewer
