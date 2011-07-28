#include <vector>
#include <math.h>
#include <TVector3.h>
#include <TMath.h>
#include <SFML/OpenGL.hpp>
#include <Viewer/Hit.hh>

namespace Viewer {

Hit::Hit( const TVector3& pos, const Colour& colour )
    : fColour( colour ), fPos( pos )
{
    TVector3 z = TVector3( 0, 0, 1 );
    TVector3 p = pos.Unit();

    TVector3 axis = z.Cross( p );
    double angle = acos( z * p  );

    std::vector< Vector3 > vertices;
    for( int i = 0; i < SIDES; i++ )
    {
        double a = 2 * TMath::Pi() * i / SIDES;
        TVector3 v = TVector3( RADIUS * sin(a), RADIUS * cos(a), pos.Mag() );
        v.Rotate( angle, axis );
        vertices.push_back( Vector3( v) );
    }

    fPolygon = Polygon( vertices );
}

void Hit::Render( bool fill ) const
{
    glPushAttrib( GL_COLOR );
    fColour.SetOpenGL();

    if( fill == false )
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    fPolygon.Render();

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glPopAttrib();
}

}; // namespace Viewer
