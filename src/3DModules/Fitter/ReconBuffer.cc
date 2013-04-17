using namespace std;

#include <TVector3.h>
#include <TMath.h>

#include <Viewer/Colour.hh>
#include <Viewer/ReconBuffer.hh>
using namespace Viewer;
#include <Viewer/RIDS/Vertex.hh>

void 
ReconBuffer::Clear()
{
  fVertices.clear();
}

void 
ReconBuffer::Render()
{
  glDisable( GL_DEPTH_TEST );
  for( map<string, VBO>::iterator iTer = fVertices.begin(); iTer != fVertices.end(); iTer++ )
    iTer->second.Render( GL_LINES );
  glEnable( GL_DEPTH_TEST );  
}

void 
ReconBuffer::AddVertex( const RIDS::Vertex& vertex,
                        const Colour& colour )
{
  TVector3 pos( vertex.GetPosition().x, vertex.GetPosition().y, vertex.GetPosition().z );
  TVector3 error( vertex.GetError().x, vertex.GetError().y, vertex.GetError().z );
  const TVector3 x0 = pos - TVector3( error.x(), 0.0, 0.0 );
  const TVector3 x1 = pos + TVector3( error.x(), 0.0, 0.0 );
  const TVector3 y0 = pos - TVector3( 0.0, error.y(), 0.0 );
  const TVector3 y1 = pos + TVector3( 0.0, error.y(), 0.0 );
  const TVector3 z0 = pos - TVector3( 0.0, 0.0, error.z() );
  const TVector3 z1 = pos + TVector3( 0.0, 0.0, error.z() );
  unsigned short i = 0;
  fVertices[vertex.GetName()].Clear();
  fVertices[vertex.GetName()].AddVertex( Vertex( x0, colour ) );
  fVertices[vertex.GetName()].AddIndex(i++);
  fVertices[vertex.GetName()].AddVertex( Vertex( x1, colour ) );
  fVertices[vertex.GetName()].AddIndex(i++);
  fVertices[vertex.GetName()].AddVertex( Vertex( y0, colour ) );
  fVertices[vertex.GetName()].AddIndex(i++);
  fVertices[vertex.GetName()].AddVertex( Vertex( y1, colour ) );
  fVertices[vertex.GetName()].AddIndex(i++);
  fVertices[vertex.GetName()].AddVertex( Vertex( z0, colour ) );
  fVertices[vertex.GetName()].AddIndex(i++);
  fVertices[vertex.GetName()].AddVertex( Vertex( z1, colour ) );
  fVertices[vertex.GetName()].AddIndex(i++);
  fVertices[vertex.GetName()].Bind();
}
