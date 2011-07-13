////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Axes3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	12/07/11 : Olivia Wasalski - New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_Axes3d__
#define __Viewer_Frames_Axes3d__

#include <cstddef>
#include <TVector3.h>
#include <Viewer/Colour.hh>

namespace Viewer {
namespace Frames {

class Axes3d {

public:

    Axes3d( double length );

    virtual ~Axes3d() { }

    void RenderAxes();

    static inline void RenderAxesSafe( Axes3d* axes )
    { if( axes != NULL ) axes->RenderAxes(); }

private:

    void RenderAxis( const TVector3& farPoint, Colour& colour );

    Colour fXColour;
    Colour fYColour;
    Colour fZColour;

    TVector3 fXPoint;
    TVector3 fYPoint;
    TVector3 fZPoint;

}; // class Axes3d

}; // namespace Frames

}; // namespace Viewer

#endif // __Viewer_Frames_Axes3d__
