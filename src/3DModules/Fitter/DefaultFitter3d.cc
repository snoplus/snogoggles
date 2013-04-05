#include <Viewer/DefaultFitter3d.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/DataSelector.hh>

#include <Viewer/RIDS/Event.hh>
#include <Viewer/RIDS/Vertex.hh>

#include <SFML/OpenGL.hpp>

#include <iostream>

namespace Viewer {
namespace Frames {

DefaultFitter3d::DefaultFitter3d()
{

}

void DefaultFitter3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{

}

void DefaultFitter3d::LoadConfiguration( const ConfigurationTable* configTable )
{

}

void DefaultFitter3d::SaveConfiguration( ConfigurationTable* configTable )
{

}

void DefaultFitter3d::EventLoop( )
{

}

void DefaultFitter3d::ProcessData( const RenderState& renderState )
{
  const RIDS::Event& event = DataSelector::GetInstance().GetEvent();
  fBuffer.Clear();
  for( int iVertex = 0; iVertex < event.GetVertexCount(); iVertex++ )
    {
      const RIDS::Vertex& vertex = event.GetVertex( iVertex );
      TVector3 pos( vertex.GetPosition().x, vertex.GetPosition().y, vertex.GetPosition().z );
      fBuffer.AddRecon( pos, renderState.GetDataColour( vertex.GetTime() ) );
    }
  fBuffer.Bind();
}

void DefaultFitter3d::Render( const RenderState& renderState )
{
  glDisable( GL_DEPTH_TEST );
  fBuffer.Render( GL_LINES );
  glEnable( GL_DEPTH_TEST );
}

}; // namespace Frames
}; // namespace Viewer
