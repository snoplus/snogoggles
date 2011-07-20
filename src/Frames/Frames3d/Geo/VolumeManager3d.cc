#include <Viewer/Volume.hh>
#include <Viewer/VolumeManager3d.hh>

namespace Viewer {
namespace Frames {

void VolumeManager3d::LoadFile()
{
    fVolume = GetVolume();
}

void VolumeManager3d::RenderGeometry()
{

}

void VolumeManager3d::RenderWireframe()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );

    fVolume->Render();

    glDisable( GL_CULL_FACE );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

}; // namespace Frames
}; // namespace Viewer
