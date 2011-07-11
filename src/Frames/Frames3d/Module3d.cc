#include <Viewer/Module3d.hh>
#include <Viewer/GUIReturn.hh>
#include <Viewer/ConfigurationTable.hh>

#include <SFML/Graphics.hpp>

#include <string>

namespace Viewer {

    class GUIManager;

namespace Frames {

void Module3d::CreateGUIObjectsSafe( Module3d* module, GUIManager& g, const sf::Rect<double>& optionsArea )
{
    if( module != NULL ) 
        module->CreateGUIObjects( g, optionsArea );
}

void Module3d::LoadConfigurationSafe( Module3d* module, ConfigurationTable& configTable )
{
    if( module != NULL ) 
        module->LoadConfiguration( configTable.GetTable( module->GetTableName() ) );
}

void Module3d::SaveConfigurationSafe( Module3d* module, ConfigurationTable& configTable )
{
    if( module != NULL ) 
    {
        ConfigurationTable* newConfigTable = configTable.NewTable( module->GetTableName() );
        newConfigTable->SetS( Module3d::ModuleTag(), module->GetName() );
        module->SaveConfiguration( newConfigTable );
    }
}

void Module3d::EventLoopSafe( Module3d* module, const GUIReturn& g )
{
    if( module != NULL ) 
        module->EventLoop( g );
}

}; // namespace Frames
}; // namespace Viewer
