#include <Viewer/ConfigurationTable.hh>
#include <Viewer/WorldLoader3d.hh>

namespace Viewer {
namespace Frames {

const std::string WorldLoader3d::FILENAME = "filename";

WorldLoader3d::WorldLoader3d( )
{
    fLoadFilename = true;
}

WorldLoader3d::WorldLoader3d( const std::string& filename )
{
    fFilename = filename;
    fLoadFilename = false;
}

void WorldLoader3d::LoadConfiguration( ConfigurationTable* configTable )
{
    if( fLoadFilename == true )
        fFilename = configTable->GetS( FILENAME );
}

void WorldLoader3d::SaveConfiguration( ConfigurationTable* configTable )
{
    if( fLoadFilename == true )
        configTable->SetS( FILENAME, fFilename );
}

}; // namepace Frames
}; // namespace Viewer
