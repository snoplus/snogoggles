#include <Viewer/WorldLoader3d.hh>
#include <Viewer/WorldManager3d.hh>
#include <Viewer/WorldBase3d.hh>

namespace Viewer {
namespace Frames {

WorldBase3d::WorldBase3d( WorldLoader3d* loader, WorldManager3d* manager )
{
    fLoader = loader;
    fManager = manager;
}

WorldBase3d::~WorldBase3d()
{
    delete fLoader;     fLoader = NULL;
    delete fManager;    fManager = NULL;
}

void WorldBase3d::CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea )
{
    fManager->CreateGUIObjects( g, optionsArea );
}

void WorldBase3d::LoadConfiguration( ConfigurationTable* configTable )
{
    fManager->LoadConfiguration( configTable );
    fLoader->LoadConfiguration( configTable );
}

void WorldBase3d::SaveConfiguration( ConfigurationTable* configTable )
{
    fManager->SaveConfiguration( configTable );
    fLoader->SaveConfiguration( configTable );
}

void WorldBase3d::LoadFile()
{
    fManager->SetWorld( fLoader->GetWorld() );
}

void WorldBase3d::EventLoop( const GUIReturn& g )
{
    fManager->EventLoop( g );
}

void WorldBase3d::RenderGeometry( )
{
    fManager->RenderGeometry();
}

}; // namespace Frames
}; // namespace Viewer
