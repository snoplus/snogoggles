#include <Viewer/Geodesic3d.hh>
#include <Viewer/PersistLabel.hh>
#include <Viewer/GeodesicSphere.hh>
#include <Viewer/GUIEvent.hh>
#include <Viewer/ConfigurationTable.hh>
using namespace Viewer;

void 
Geodesic3d::EventLoop()
{
  while( !fEvents.empty() )
    {
      if( !fEvents.front().IsNULL() )
        fDisplay = !fDisplay;
      fEvents.pop();
    }
}

void 
Geodesic3d::SaveConfiguration( ConfigurationTable* configTable )
{
  configTable->SetI( "Display", fDisplay );
}

void 
Geodesic3d::PreInitialise( const ConfigurationTable* configTable )
{
  sf::Rect<double> size;
  size.left = 0.0;
  size.top = 0.0;
  size.width = 1.0;
  size.height = 1.0;
  GUIs::PersistLabel* display = dynamic_cast<GUIs::PersistLabel*>( fGUIManager.NewGUI<GUIs::PersistLabel>( size ) );
  display->Initialise( 14, "Display Geodesic" );
  if( configTable != NULL )
    fDisplay = static_cast<bool>( configTable->GetI( "Display" ) );
  display->SetState( fDisplay );
}

void
Geodesic3d::Render3d()
{
  if( !fDisplay )
    return;
  GeodesicSphere::GetInstance()->Render();
}
