////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::HitRenderer3d
///
/// \brief   Responsible rendering hits.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
//      08/07/11 : Olivia Wasalski - First Revision, New File. \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_HitRenderer3d__
#define __Viewer_Frames_HitRenderer3d__

#include <TVector3.h>

namespace Viewer {
namespace Frames {

class HitRenderer3d {

public:

    static void RenderSolidHit( const TVector3& pos );

    static void RenderHollowHit( const TVector3& pos );

    static void RotateToRenderHit( const TVector3& pos );

    static void RenderHexagonOnBallSolid( const TVector3& pos );

    static void RenderHexagonOnBallHollow( const TVector3& pos );

    static void DrawPMT( const TVector3& pmtPos, const TVector3& pmtDir, bool fill );

private:

    static const int NUM_VERTICES_IN_HEXAGON = 6;
    static const float RADIUS = 140.0f;

}; // class HitRenderer3d

}; // namespace Frames 
}; // namespace Viewer

#endif // Viewer_Frames_HitRenderer3d_hh
