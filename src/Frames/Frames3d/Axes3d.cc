#include <Viewer/Axes3d.hh>
#include <Viewer/Colour.hh>

#include <SFML/OpenGL.hpp>
#include <iostream>

namespace Viewer {
namespace Frames {

Axes3d::Axes3d( double length ) 
{ 
    // TODO: Update when the rainbow colour palette is ready.
    fXColour = Colour( 255, 0, 0 );
    fYColour = Colour( 0, 255, 0 );
    fZColour = Colour( 0, 0, 255 );

    fXPoint = length * TVector3( 1, 0, 0 );
    fYPoint = length * TVector3( 0, 1, 0 );
    fZPoint = length * TVector3( 0, 0, 1 );
}

void Axes3d::RenderAxes( )
{
    RenderAxis( fXPoint, fXColour );
    RenderAxis( fYPoint, fYColour );
    RenderAxis( fZPoint, fZColour);
}

void Axes3d::RenderAxis( const TVector3& p, Colour& colour )
{
    glPushAttrib( GL_COLOR );
    colour.SetOpenGL();

    glBegin( GL_LINES );
    glVertex3f( 0, 0, 0 );
    glVertex3f( p.X(), p.Y(), p.Z() );
    glEnd();

    glPopAttrib();
}

}; // namespace Frames
}; // namespace Viewer
