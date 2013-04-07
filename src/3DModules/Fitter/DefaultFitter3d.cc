#include <Viewer/DefaultFitter3d.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

void
DefaultFitter3d::ProcessData( const RenderState& renderState )
{
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  fBuffer.Clear();
  for( int iVertex = 0; iVertex < event.GetVertexCount(); iVertex++ )
    {
      const RIDS::Vertex& vertex = event.GetVertex( iVertex );
      TVector3 pos( vertex.GetPosition().x, vertex.GetPosition().y, vertex.GetPosition().z );
      fBuffer.AddRecon( pos, GUIProperties::GetInstance().GetColourPalette().GetColour( iVertex ) );
    }
  fBuffer.Bind();
}

void
DefaultFitter3d::Render3d()
{
  glDisable( GL_DEPTH_TEST );
  fBuffer.Render( GL_LINES );
  glEnable( GL_DEPTH_TEST );
}
