////////////////////////////////////////////////////////////////////////
/// \class Viewer::Hit
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     12/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Hit__
#define __Viewer_Hit__

#include <Viewer/Colour.hh>
#include <Viewer/Polygon.hh>

namespace Viewer
{
class Hit {
public:
    Hit( const TVector3& pos, const Colour& colour );
    void Render( bool fill ) const;
    inline TVector3 GetPos() const;

private:
    TVector3 fPos;
    Polygon fPolygon;
    Colour fColour;

    static const double RADIUS = 140.0;
    static const int SIDES = 6;

}; // class Hit

////////////////////////////////////////////////////////////////////////
// inline method
////////////////////////////////////////////////////////////////////////

TVector3 Hit::GetPos() const
{
    return fPos;
}

} // ::Viewer

#endif // __Viewer_Hit
