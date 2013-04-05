#include <iostream>
using namespace std;

#include <TVector3.h>
#include <TMath.h>

#include <Viewer/Colour.hh>
#include <Viewer/ReconBuffer.hh>
using namespace Viewer;

void 
ReconBuffer::AddRecon( const TVector3& pos, 
                       const Colour& colour )
{
  const double size = 200.0;
  const TVector3 x0 = pos - TVector3( size, 0.0, 0.0 );
  const TVector3 x1 = pos + TVector3( size, 0.0, 0.0 );
  const TVector3 y0 = pos - TVector3( 0.0, size, 0.0 );
  const TVector3 y1 = pos + TVector3( 0.0, size, 0.0 );
  const TVector3 z0 = pos - TVector3( 0.0, 0.0, size );
  const TVector3 z1 = pos + TVector3( 0.0, 0.0, size );
  unsigned short i = fVertices.size();
  AddVertex( Vertex( x0, colour ) );
  AddIndex(i++);
  AddVertex( Vertex( x1, colour ) );
  AddIndex(i++);
  AddVertex( Vertex( y0, colour ) );
  AddIndex(i++);
  AddVertex( Vertex( y1, colour ) );
  AddIndex(i++);
  AddVertex( Vertex( z0, colour ) );
  AddIndex(i++);
  AddVertex( Vertex( z1, colour ) );
  AddIndex(i++);
}
