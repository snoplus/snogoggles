#include <TVector3.h>
#include <Viewer/Colour.hh>
#include <Viewer/Vertex.hh>

#define COLOUR 255.0f

namespace Viewer {

Vertex::Vertex( const TVector3& pos, const Colour& colour )
{
    fData.x = pos.X();          fData.y = pos.Y();          fData.z = pos.Z();
    fData.r = colour.r/COLOUR;  fData.g = colour.g/COLOUR;  fData.b = colour.b/COLOUR;
    fData.a = colour.a/COLOUR;
}

}; // namespace Viewer
