#include <Viewer/Arcball3d.hh>
#include <Viewer/ConfigTableUtils.hh>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <TVector3.h>
#include <string>

namespace Viewer {
namespace Frames {

Arcball3d::Arcball3d()
{
  fRadius = 8900.0;
  fCameraDist = 3.5;
  fCamera.SetXYZ(fCameraDist*fRadius, 0, 0);
  fEye.SetXYZ(0,0,0);
  fUp.SetXYZ(0,0,1);
  fZoom = (MAX_ZOOM + MIN_ZOOM) / 2;
}

void Arcball3d::CreateGUIObjects( GUIManager* g, const sf::Rect<double>& optionsArea )
{

}

void Arcball3d::CreateDragArea( GUIManager* g, const sf::Rect<double>& draggableArea )
{

}

void Arcball3d::LoadConfiguration( ConfigurationTable* configTable )
{
    fRadius = configTable->GetD( RadiusTag() );
    fCameraDist = configTable->GetD( CameraDistTag() );
    fZoom = configTable->GetD( ZoomTag() );

    fCamera = ConfigTableUtils::GetTVector3( configTable, CameraTag() );
    fEye = ConfigTableUtils::GetTVector3( configTable, EyeTag() );
    fUp = ConfigTableUtils::GetTVector3( configTable, UpTag() );
}

void Arcball3d::SaveConfiguration( ConfigurationTable* configTable )
{
    configTable->SetD( RadiusTag(), fRadius );
    configTable->SetD( CameraDistTag(), fCameraDist );
    configTable->SetD( ZoomTag(), fZoom );

    ConfigTableUtils::SetTVector3( configTable, CameraTag(), fCamera );
    ConfigTableUtils::SetTVector3( configTable, EyeTag(), fEye );
    ConfigTableUtils::SetTVector3( configTable, UpTag(), fUp );
}

void Arcball3d::EventLoop( const GUIReturn& g )
{

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

bool Arcball3d::IsFront( TVector3 v )
{
    if (fCamera*v >= 0) return true;
    else return false;
}

}; // namespace Frames
}; // namespace Viewer
