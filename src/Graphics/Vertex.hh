////////////////////////////////////////////////////////////////////////
/// \class Vertex
///
/// \brief   Stores the data needed to render a vertex in OpenGL.
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     01/05/12 : O.Wasalski - First Revision, new file. \n
///
/// \detail  Stores the data needed to render a vertex in a struct, so
///          that the absolute offsets between fields can be easily 
///          calculated. Padding is necessary to align the vertex data
///          struct to 32 bytes to increase performance. Each vertex
///          specifies a position in 3D space and a colour. Decided not
///          to include normal vertex or texture coordinates due to
///          symbolic representation of most objects. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Vertex__
#define __Viewer_Vertex__

class TVector3;

namespace Viewer {
    class Colour;

class Vertex {
public:

    struct Data {
        float x, y, z;
        float r, g, b, a;
        float padding;
    };  // struct Data

    struct Data fData;

    Vertex() { };
    Vertex( const TVector3& pos, const Colour& colour );
};

} // namespace Viewer

#endif
