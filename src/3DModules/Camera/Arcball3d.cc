#include <Viewer/Arcball3d.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/SpriteTimer.hh>
#include <Viewer/Arcball.hh>
#include <Viewer/GUIManager.hh>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <TVector3.h>
#include <string>
#include <iostream>

namespace Viewer {
namespace Frames {

const std::string Arcball3d::CAMERA_TAG = "Camera";
const std::string Arcball3d::EYE_TAG = "Eye";
const std::string Arcball3d::UP_TAG = "Up";
const std::string Arcball3d::RADIUS_TAG = "Radius";
const std::string Arcball3d::CAMERA_DIST_TAG = "CameraDist";
const std::string Arcball3d::ZOOM_TAG = "Zoom";

Arcball3d::Arcball3d()
{
    fRadius = 8500.0;
    fCameraDist = 3.5;
    fCamera.SetXYZ(fCameraDist*fRadius, 0, 0);
    fEye.SetXYZ(0,0,0);
    fUp.SetXYZ(0,0,1);
    fZoom = (MAX_ZOOM + MIN_ZOOM) / 2;
    fSpinSpeed = 0.001;
    fZoomSpeed = 0.0001;

    double size = 10000;
    fPlane[0] = TVector3( 0, size, size );
    fPlane[1] = TVector3( 0, -size, size );
    fPlane[2] = TVector3( 0, -size, -size );
    fPlane[3] = TVector3( 0, size, -size );
}

void Arcball3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{

}

void Arcball3d::CreateDragArea( GUIManager& g, const sf::Rect<double>& draggableArea )
{
    // TODO: Needs to be completed.
    fArcball = g.NewGUI<GUIs::Arcball>( draggableArea );
    fArcball->Initialise( fRadius );
}

void Arcball3d::LoadConfiguration( const ConfigurationTable* configTable )
{
    ConfigTableUtils::GetDSafe( configTable, RADIUS_TAG, fRadius );
    ConfigTableUtils::GetDSafe( configTable, CAMERA_DIST_TAG, fCameraDist );
    ConfigTableUtils::GetDSafe( configTable, ZOOM_TAG, fZoom );
    fCamera.SetXYZ(fCameraDist*fRadius, 0, 0);
}

void Arcball3d::SaveConfiguration( ConfigurationTable* configTable )
{
    configTable->SetD( RADIUS_TAG, fRadius );
    configTable->SetD( CAMERA_DIST_TAG, fCameraDist );
    configTable->SetD( ZOOM_TAG, fZoom );
}

void Arcball3d::EventLoop( )
{

}

void Arcball3d::SetUpCameraSystem( const sf::Rect<double>& viewportRect )
{
    sf::Rect<double> rect = fArcball->GetRect()->GetRect( Rect::eGL );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f * fZoom, rect.Width/rect.Height, 
        (fCameraDist - 1.1)*fRadius, (fCameraDist + 1.1)*fRadius);
    glViewport( (GLint)rect.Left, (GLint)rect.Top, (GLsizei)rect.Width, (GLsizei)rect.Height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        fCamera.X(), fCamera.Y(), fCamera.Z(),
        fEye.X(), fEye.Y(), fEye.Z(),
        fUp.X(), fUp.Y(), fUp.Z()
    );

    RenderScreen();

    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT, viewport );

    GLdouble model[16];
    glGetDoublev( GL_MODELVIEW_MATRIX, model );

    GLdouble proj[16];
    glGetDoublev( GL_PROJECTION_MATRIX, proj );

    Rotation r = fArcball->Update( viewport, model, proj );
    r.GLRotate();

    if( fArcball->GetState() == false )
    {
        r.Rotate( fCamera );
        r.Rotate( fUp );
        for( int i = 0; i < 4; i++ )
            r.Rotate( fPlane[i] );
    }
}

void Arcball3d::RenderScreen()
{
    glEnable( GL_DEPTH_TEST );
    glColorMask( GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE );
    glBegin( GL_QUADS );

    for( int i = 0; i < 4; i++ ) 
        glVertex3f( fPlane[i].X(), fPlane[i].Y(), fPlane[i].Z() );

    glEnd();
    glDisable( GL_DEPTH_TEST );
    glColorMask( GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE );
}


}; // namespace Frames
}; // namespace Viewer
