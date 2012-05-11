#include <math.h>
#include <TVector3.h>
#include <Viewer/Colour.hh>
#include <Viewer/Sphere.hh>

#define PI 3.14159265
#define RADIUS 8000

namespace Viewer {

Sphere::Sphere()
{
    for( int phi = 0; phi <= 360; phi++ )
    {
        for( int theta = 0; theta <= 180; theta++ )
        {
            unsigned int b = fVertices.size();

            AddVertex( Vertex( RADIUS*TVector3( cos(phi/PI)*sin(theta/PI), sin(phi/PI)*sin(theta/PI), cos(theta/PI) ), Colour() ) );
            AddVertex( Vertex( RADIUS*TVector3( cos((phi+1)/PI)*sin(theta/PI), sin((phi+1)/PI)*sin(theta/PI), cos(theta/PI) ), Colour() ) );
            AddVertex( Vertex( RADIUS*TVector3( cos((phi+1)/PI)*sin((theta+1)/PI), sin((phi+1)/PI)*sin((theta+1)/PI), cos((theta+1)/PI) ), Colour() ) );
            AddVertex( Vertex( RADIUS*TVector3( cos(phi/PI)*sin((theta+1)/PI), sin(phi/PI)*sin((theta+1)/PI), cos((theta+1)/PI) ), Colour() ) );

            AddIndex(b+0); AddIndex(b+1); AddIndex(b+2); 
            AddIndex(b+0); AddIndex(b+2); AddIndex(b+3); 
        }
    }
}

}; // namespace Viewer
