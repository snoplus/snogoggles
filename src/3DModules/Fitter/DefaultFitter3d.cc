#include <Viewer/DefaultFitter3d.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
using namespace Viewer;

void
DefaultFitter3d::ProcessEvent( const RenderState& renderState )
{
  fBuffer.Clear();
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  for( int iVertex = 0; iVertex < event.GetVertexCount(); iVertex++ )
    {
      const RIDS::Vertex& vertex = event.GetVertex( iVertex );
      fBuffer.AddVertex( vertex, GUIProperties::GetInstance().GetColourPalette().GetColour( iVertex ) );
    }
}

void
DefaultFitter3d::Render3d()
{
  fBuffer.Render();
}
