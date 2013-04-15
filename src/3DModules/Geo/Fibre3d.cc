#include <TVector3.h>
#include <TMath.h>

#include <Viewer/Fibre3d.hh>
#include <Viewer/DataSelector.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIEvent.hh>
using namespace Viewer;
#include <Viewer/RIDS/FibreList.hh>

const int kSize = 600.0;

void
Fibre3d::EventLoop()
{
  while( !fEvents.empty() )
    {
      switch( fEvents.front().fguiID )
        {
        case 0: // AMELLIE
          fDisplayAMELLIE = !fDisplayAMELLIE;
          break;
        case 1: // SMELLIE
          fDisplaySMELLIE = !fDisplaySMELLIE;
          break;
        case 2: // TELLIE
          fDisplayTELLIE = !fDisplayTELLIE;
          break;
        }
      fEvents.pop();
    }
}

void
Fibre3d::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "DisplayAMELLIE", fDisplayAMELLIE );
  configTable->SetI( "DisplaySMELLIE", fDisplaySMELLIE );
  configTable->SetI( "DisplayTELLIE", fDisplayTELLIE );
}

void
Fibre3d::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> size;
  size.left = 0.0;
  size.top = 0.0;
  size.width = 0.3;
  size.height = 1.0;
  GUIs::PersistLabel* displayAMELLIE = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  displayAMELLIE->Initialise( 16, "Display AMELLIE" );
  if( configTable != NULL )
    fDisplayAMELLIE = static_cast<bool>( configTable->GetI( "DisplayAMELLIE" ) );
  displayAMELLIE->SetState( fDisplayAMELLIE );
  size.left += size.width;
  GUIs::PersistLabel* displaySMELLIE = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  displaySMELLIE->Initialise( 16, "Display SMELLIE" );
  if( configTable != NULL )
    fDisplaySMELLIE = static_cast<bool>( configTable->GetI( "DisplaySMELLIE" ) );
  displaySMELLIE->SetState( fDisplaySMELLIE );
  size.left += size.width;
  GUIs::PersistLabel* displayTELLIE = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  displayTELLIE->Initialise( 16, "Display TELLIE" );
  if( configTable != NULL )
    fDisplayTELLIE = static_cast<bool>( configTable->GetI( "DisplayTELLIE" ) );
  displayTELLIE->SetState( fDisplayTELLIE );
}

void
Fibre3d::ProcessData( const RenderState& renderState )
{
  const RIDS::FibreList& fibreList = DataSelector::GetInstance().GetFibreList();
  fAMELLIEPos.Clear();
  fAMELLIEDir.Clear();
  fSMELLIEPos.Clear();
  fSMELLIEDir.Clear();
  fTELLIEPos.Clear();
  fTELLIEDir.Clear();
  for( size_t iFibre = 0; iFibre < fibreList.GetFibreCount(); iFibre++ )
    {
      switch( fibreList.GetType( iFibre ) )
        {
        case RIDS::FibreList::eAMELLIE:
          AddPosVertices( fAMELLIEPos, 
                          fibreList.GetPosition( iFibre ), 
                          GUIProperties::GetInstance().GetColourPalette().GetColour( 0 ) );
          AddDirVertices( fAMELLIEDir, 
                          fibreList.GetPosition( iFibre ), 
                          fibreList.GetDirection( iFibre ),
                          GUIProperties::GetInstance().GetColourPalette().GetColour( 0 ) );
          break;
        case RIDS::FibreList::eSMELLIE:
          AddPosVertices( fSMELLIEPos, 
                          fibreList.GetPosition( iFibre ), 
                          GUIProperties::GetInstance().GetColourPalette().GetColour( 1 ) );
          AddDirVertices( fSMELLIEDir, 
                          fibreList.GetPosition( iFibre ), 
                          fibreList.GetDirection( iFibre ),
                          GUIProperties::GetInstance().GetColourPalette().GetColour( 1 ) );
          break;
        case RIDS::FibreList::eTELLIE:
          AddPosVertices( fTELLIEPos, 
                          fibreList.GetPosition( iFibre ), 
                          GUIProperties::GetInstance().GetColourPalette().GetColour( 2 ) );
          AddDirVertices( fTELLIEDir, 
                          fibreList.GetPosition( iFibre ), 
                          fibreList.GetDirection( iFibre ),
                          GUIProperties::GetInstance().GetColourPalette().GetColour( 2 ) );
          break;
        }
    }
  fAMELLIEPos.Bind();
  fAMELLIEDir.Bind();
  fSMELLIEPos.Bind();
  fSMELLIEDir.Bind();
  fTELLIEPos.Bind();
  fTELLIEDir.Bind();
}

void
Fibre3d::Render3d()
{
  glDisable( GL_DEPTH_TEST );
  if( fDisplayAMELLIE )
    {
      fAMELLIEPos.Render( GL_TRIANGLES );
      fAMELLIEDir.Render( GL_LINES );
    }
  if( fDisplaySMELLIE )
    {
      fSMELLIEPos.Render( GL_TRIANGLES );
      fSMELLIEDir.Render( GL_LINES );
    }
  if( fDisplayTELLIE )
    {
      fTELLIEPos.Render( GL_TRIANGLES );
      fTELLIEDir.Render( GL_LINES );
    }
  glEnable( GL_DEPTH_TEST );
}

void
Fibre3d::AddPosVertices( VBO& vbo, 
                         const sf::Vector3<double>& pos,
                         const Colour& colour )
{
  const TVector3 z = TVector3( 0, 0, 1 );
  TVector3 p( pos.x, pos.y, pos.z );

  const TVector3 axis = z.Cross( p.Unit() );
  const double angle = acos( z * p.Unit()  );

  for( int iLoop = 0; iLoop < 3; iLoop++ )
    {
      double a = 2 * TMath::Pi() * iLoop / 3.0;
      TVector3 v = TVector3( kSize * sin(a) / 2.0, kSize * cos(a) / 2.0, p.Mag() );
      v.Rotate( angle, axis );
      vbo.AddVertex( Vertex( v, colour ) );
      vbo.AddIndex( vbo.fIndices.size() );
    }
}

void
Fibre3d::AddDirVertices( VBO& vbo,
                         const sf::Vector3<double>& pos,
                         const sf::Vector3<double>& dir,
                         const Colour& colour )
{
  const TVector3 p( pos.x, pos.y, pos.z );
  const TVector3 pdir( dir.x, dir.y, dir.z );
  const TVector3 p2 = p + pdir * kSize;
  vbo.AddVertex( Vertex( p, colour ) );
  vbo.AddVertex( Vertex( p2, colour ) );
  vbo.AddIndex( vbo.fIndices.size() );
  vbo.AddIndex( vbo.fIndices.size() );
}
