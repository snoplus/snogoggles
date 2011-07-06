#include <Viewer/Module3d.hh>
#include <Viewer/GUIReturn.hh>
#include <Viewer/ConfigurationTable.hh>

#include <SFML/Graphics.hpp>

namespace Viewer {

    class GUIManager;

namespace Frames {

void Module3d::CreateGUIObjectsSafe( Module3d* module, GUIManager* g, const sf::Rect<double>& optionsArea )
{
    if( module != NULL ) 
        module->CreateGUIObjects( g, optionsArea );
}

void Module3d::LoadConfigurationSafe( Module3d* module, ConfigurationTable& configTable )
{
//    if( module != NULL ) 
//        module->LoadConfiguration( configTable.GetNextTable( module->GetTableName() ) );
}

void Module3d::SaveConfigurationSafe( Module3d* module, ConfigurationTable& configTable )
{
//    if( module != NULL ) 
//        module->SaveConfiguration( configTable.NewTable( module->GetTableName() ) );
}

void Module3d::EventLoopSafe( Module3d* module, const GUIReturn& g )
{
    if( module != NULL ) 
        module->EventLoop( g );
}

}; // namespace Frames
}; // namespace Viewer
