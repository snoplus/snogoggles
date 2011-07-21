#include <Viewer/XML3d.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/World.hh>
#include <Viewer/VisAttributes.hh>
#include <Viewer/GeoTranslator.hh>

namespace Viewer {
namespace Frames {

World* XML3d::GetWorld()
{
    Configuration config = Configuration( GetFilename(), false );

    std::vector< ConfigurationTable* >::iterator itr;
    itr = config.GetTableBegin();

    return GeoTranslator::GetWorld( *itr );
}


}; // namespace Frames
}; // namespace Viewer
