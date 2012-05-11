////////////////////////////////////////////////////////////////////////
/// \class Vertex
///
/// \brief   
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     01/05/12 : O.Wasalski - First Revision, new file. \n
///
/// \detail  
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
