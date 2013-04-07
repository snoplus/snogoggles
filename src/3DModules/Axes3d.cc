#include <Viewer/Axes3d.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/GUIEvent.hh>
using namespace Viewer;

const double kSize = 9000.0;

void 
Axes3d::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( !fEvents.front().IsNULL() )
        fDisplay = !fDisplay;
      fEvents.pop();
    }
}

void 
Axes3d::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "Display", fDisplay );
}

void 
Axes3d::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> size;
  size.left = 0.0;
  size.top = 0.0;
  size.width = 1.0;
  size.height = 1.0;
  GUIs::PersistLabel* display = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  display->Initialise( 14, "Display Axes" );
  if( configTable != NULL )
    fDisplay = static_cast<bool>( configTable->GetI( "Display" ) );
  display->SetState( fDisplay );
}

void
Axes3d::Render3d()
{
  if( !fDisplay )
    return;
  RenderAxis( sf::Vector3<double>( kSize, 0.0, 0.0 ),
              GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eRed ) );
  RenderAxis( sf::Vector3<double>( 0.0, kSize, 0.0 ),
              GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eGreen ) );
  RenderAxis( sf::Vector3<double>( 0.0, 0.0, kSize ),
              GUIProperties::GetInstance().GetColourPalette().GetPrimaryColour( eBlue ) );
}

void 
Axes3d::RenderAxis( const sf::Vector3<double>& point, 
                    Colour colour )
{
  glDisable( GL_DEPTH_TEST );
  glPushAttrib( GL_COLOR );
  colour.SetOpenGL();

  glBegin( GL_LINES );
  glVertex3f( 0, 0, 0 );
  glVertex3f( point.x, point.y, point.z );
  glEnd();

  glPopAttrib();
  glEnable( GL_DEPTH_TEST );
}
