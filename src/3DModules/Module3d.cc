#include <Viewer/Module3d.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/RenderState.hh>
#include <Viewer/GUIProperties.hh>
#include <Viewer/DataStore.hh>

#include <SFML/Graphics.hpp>

#include <string>

namespace Viewer {

    class GUIManager;

namespace Frames {

const std::string Module3d::MODULE_TAG = "type";

void Module3d::CreateGUIObjectsSafe( Module3d* module, GUIManager& g, const sf::Rect<double>& optionsArea )
{
    if( module != NULL ) 
        module->CreateGUIObjects( g, optionsArea );
}

void Module3d::LoadConfigurationSafe( Module3d* module, 
                                      const ConfigurationTable* configTable )
{
    if( module != NULL ) 
    {
        try { module->LoadConfiguration( configTable->GetTable( module->GetTableName() ) ); }
        catch( ConfigurationTable::NoTableError& e ) { }
    }
}

void Module3d::SaveConfigurationSafe( Module3d* module, 
                                      ConfigurationTable* configTable )
{
    if( module != NULL ) 
    {
        ConfigurationTable* newConfigTable = configTable->NewTable( module->GetTableName() );
        newConfigTable->SetS( MODULE_TAG, module->GetName() );
        module->SaveConfiguration( newConfigTable );
    }
}

void Module3d::EventLoopSafe( Module3d* module )
{
    if( module != NULL ) 
        module->EventLoop( );
}

bool Module3d::StateChanged( const RenderState& renderState )
{
    if( renderState.HasChanged() ) return true;
    if( GUIProperties::GetInstance().HasChanged() ) return true;
    if( DataStore::GetInstance().HasChanged() ) return true;
    return false;
}

}; // namespace Frames
}; // namespace Viewer
