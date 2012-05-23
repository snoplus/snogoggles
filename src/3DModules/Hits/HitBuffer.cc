#include <iostream>
#include <math.h>
#include <TVector3.h>
#include <TMath.h>
#include <Viewer/Colour.hh>
#include <Viewer/HitBuffer.hh>

#define SIDES 6
#define RADIUS 140

namespace Viewer {

void HitBuffer::AddHitVertices( const TVector3& pos, const Colour& colour )
{
    TVector3 z = TVector3( 0, 0, 1 );
    TVector3 p = pos.Unit();

    TVector3 axis = z.Cross( p );
    double angle = acos( z * p  );

    for( int i = 0; i < SIDES; i++ )
    {
        double a = 2 * TMath::Pi() * i / SIDES;
        TVector3 v = TVector3( RADIUS * sin(a), RADIUS * cos(a), pos.Mag() );
        v.Rotate( angle, axis );
        fVertices.push_back( Vertex(v,colour).fData );
    }


}

void HitBuffer::AddHitFull( const TVector3& pos, const Colour& colour )
{
    unsigned int b = fVertices.size();
    AddHitVertices( pos, colour );
    fIndices.push_back(b+0);    fIndices.push_back(b+1);    fIndices.push_back(b+2);
    fIndices.push_back(b+0);    fIndices.push_back(b+2);    fIndices.push_back(b+3);
    fIndices.push_back(b+0);    fIndices.push_back(b+3);    fIndices.push_back(b+4);
    fIndices.push_back(b+0);    fIndices.push_back(b+4);    fIndices.push_back(b+5);
}

void HitBuffer::AddHitOutline( const TVector3& pos, const Colour& colour )
{
    unsigned int b = fVertices.size();
    AddHitVertices( pos, colour );
    fIndices.push_back(b+0);    fIndices.push_back(b+1);
    fIndices.push_back(b+1);    fIndices.push_back(b+2);
    fIndices.push_back(b+2);    fIndices.push_back(b+3);
    fIndices.push_back(b+3);    fIndices.push_back(b+4);
    fIndices.push_back(b+4);    fIndices.push_back(b+5);
    fIndices.push_back(b+5);    fIndices.push_back(b+0);
}

}; // namespace Viewer
