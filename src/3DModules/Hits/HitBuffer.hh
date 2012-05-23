////////////////////////////////////////////////////////////////////////
/// \class HitBuffer
///
/// \brief  Special VBO to create, store and render vertices for hits.
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
///     01/05/12 : O.Wasalski - First Revision, new file. \n
///
/// \detail  Wraps the creation of the hexagons for each hit in methods
///          detailing the creation of either a full or outline hexagon.
///          Rendering is done using the parent VBO class. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_HitBuffer__
#define __Viewer_HitBuffer__

class TVector3;
#include <Viewer/VBO.hh>

namespace Viewer {
    class Colour;

class HitBuffer : public VBO {
public:
    void AddHitFull( const TVector3& pos, const Colour& colour );
    void AddHitOutline( const TVector3& pos, const Colour& colour );

private:
    void AddHitVertices( const TVector3& pos, const Colour& colour );
};

} // namespace Viewer

#endif
