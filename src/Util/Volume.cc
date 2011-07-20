#include <SFML/OpenGL.hpp>
#include <Viewer/Volume.hh>

namespace Viewer {

const std::string Volume::NAME_TAG = "name";
const std::string Volume::VISIBLE_TAG = "visible";
const std::string Volume::COLOUR_TAG = "colour";
const std::string Volume::TRANSLATION_TAG = "translation";
const std::string Volume::ROTATION_AXIS_TAG = "rotationAxis";
const std::string Volume::ROTATION_ANGLE_TAG = "rotationAngle";
const std::string Volume::POLYHEDRON_TAG = "polyhedron";

void Volume::Render()
{
    glPushMatrix();
    glTranslatef( fTranslation.x(), fTranslation.y(), fTranslation.z() );
    glRotatef( fRotationAngle, fRotationAxis.x(), fRotationAxis.y(), fRotationAxis.z() );

    glPushAttrib( GL_COLOR );
    fColour.SetOpenGL();

    if( fVisible == true )
        fPolyhedron.RenderOpenGL();

    glPopAttrib();

    for( int i = 0; i < fDaughterVolumes.size(); i++ )
        fDaughterVolumes.at(i)->Render();

    glPopMatrix();
}

}; // namespace Viewer
