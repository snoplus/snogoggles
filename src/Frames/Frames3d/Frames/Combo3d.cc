#include <Viewer/Combo3d.hh>
#include <Viewer/ModuleFactory3d.hh>
#include <Viewer/CameraManager3d.hh>

namespace Viewer {
namespace Frames {

void Combo3d::CreateGUIObjects()
{
    fCameraManager->CreateGUIObjects( fGUIManager, sf::Rect< double >( 0, 0.92, 0.48, 0.08 ) );
}

void Combo3d::LoadConfiguration( ConfigurationTable& configTable )
{
    ModuleFactory3d::GetInstance()->SetAllModuleTypes( this, configTable );
    LoadWithoutSettingModules( configTable );
}

}; // namespace Frames
}; // namespace Viewer
