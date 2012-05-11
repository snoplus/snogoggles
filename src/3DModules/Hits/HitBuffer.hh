////////////////////////////////////////////////////////////////////////
/// \class HitBuffer
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
