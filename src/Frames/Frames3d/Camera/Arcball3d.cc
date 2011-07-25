#include <Viewer/Arcball3d.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/SpriteTimer.hh>
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
    fRadius = 8900.0;
    fCameraDist = 3.5;
    fCamera.SetXYZ(fCameraDist*fRadius, 0, 0);
    fEye.SetXYZ(0,0,0);
    fUp.SetXYZ(0,0,1);
    fZoom = (MAX_ZOOM + MIN_ZOOM) / 2;
    fSpinSpeed = 0.001;
    fZoomSpeed = 0.0001;
}

void Arcball3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    // TODO: Needs to be completed.
    float width = 0.1;
    float height = width;
    float left = 0;
    float top = 1 - height;

    sf::Rect<double> leftRect( left, top, width, height); 
    fSpinLeftButton = g.NewGUI<GUIs::SpriteTimer>( leftRect );
    fSpinLeftButton->SetSprite("Arrows/RotateLeft.png");

    sf::Rect<double> rightRect( left + width, top, width, height); 
    fSpinRightButton = g.NewGUI<GUIs::SpriteTimer>( rightRect );
    fSpinRightButton->SetSprite("Arrows/RotateRight.png");

    sf::Rect<double> upRect( left + 2*width, top, width, height);
    fSpinUpButton = g.NewGUI<GUIs::SpriteTimer>( upRect );
    fSpinUpButton->SetSprite("Arrows/RotateUp.png");

    sf::Rect<double> downRect( left + 3*width, top, width, height);
    fSpinDownButton = g.NewGUI<GUIs::SpriteTimer>( downRect );
    fSpinDownButton->SetSprite("Arrows/RotateDown.png");

    sf::Rect<double> zoomInRect( left + 4*width, top, width, height);
    fZoomInButton = g.NewGUI<GUIs::SpriteTimer>( zoomInRect );
    fZoomInButton->SetSprite("ZoomIn.png");

    sf::Rect<double> zoomOutRect( left + 5*width, top, width, height);
    fZoomOutButton = g.NewGUI<GUIs::SpriteTimer>( zoomOutRect );
    fZoomOutButton->SetSprite("ZoomOut.png");
}

void Arcball3d::CreateDragArea( GUIManager& g, const sf::Rect<double>& draggableArea )
{
    // TODO: Needs to be completed.
}

void Arcball3d::LoadConfiguration( ConfigurationTable* configTable )
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
    SpinButton( fUp, fSpinLeftButton );
    SpinButton( -fUp, fSpinRightButton );
    SpinButton( fCamera.Cross( fUp ), fSpinUpButton );
    SpinButton( fCamera.Cross( fUp ), fSpinDownButton );
    ZoomButton( -fZoomSpeed, fZoomInButton );
    ZoomButton( fZoomSpeed, fZoomOutButton );
}

void Arcball3d::SetUpCameraSystem( const sf::Rect<double>& viewportRect )
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.f * fZoom, viewportRect.Width/viewportRect.Height, 0.1f*fRadius, 100.f*fRadius);
    glViewport( (GLint)viewportRect.Left, (GLint)viewportRect.Top, (GLsizei)viewportRect.Width, (GLsizei)viewportRect.Height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        fCamera.X(), fCamera.Y(), fCamera.Z(),
        fEye.X(), fEye.Y(), fEye.Z(),
        fUp.X(), fUp.Y(), fUp.Z()
    );

}

bool Arcball3d::IsFront( const TVector3& v )
{
    if ( fCamera * v >= 0 ) return true;
    else return false;
}

void Arcball3d::Spin( const TVector3& axis, int deltaTime )
{
    fCamera.Rotate( fSpinSpeed * deltaTime, axis );
    fUp.Rotate( fSpinSpeed * deltaTime, axis );
}

void Arcball3d::Zoom( float speed, int deltaTime )
{
    fZoom += speed * deltaTime;

    if( fZoom > MAX_ZOOM ) fZoom = MAX_ZOOM;
    else if( fZoom < MIN_ZOOM ) fZoom = MIN_ZOOM;
}

void Arcball3d::SpinButton( const TVector3& axis, GUIs::Timer* timer )
{
    if( timer->GetState() == true )
        Spin( axis, timer->GetDeltaTime() );
}

void Arcball3d::ZoomButton( float speed, GUIs::Timer* timer )
{
    if( timer->GetState() == true )
        Zoom( speed, timer->GetDeltaTime() );
}

}; // namespace Frames
}; // namespace Viewer
