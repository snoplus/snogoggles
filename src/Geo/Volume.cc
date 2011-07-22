#include <SFML/OpenGL.hpp>
#include <Viewer/Volume.hh>
#include <Viewer/VisAttributes.hh>
#include <iostream>

namespace Viewer {

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

}; // namespace Viewer
