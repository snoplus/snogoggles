#include <Viewer/XML3d.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/ConfigTableUtils.hh>
#include <Viewer/ConfigurationTable.hh>

namespace Viewer {
namespace Frames {

Volume* XML3d::GetVolume()
{
    Configuration config = Configuration( GetFilename(), false );

    std::vector< ConfigurationTable* >::iterator itr;
    itr = config.GetTableBegin();

    return ConfigTableUtils::GetVolume( *itr );
}

}; // namespace Frames
}; // namespace Viewer
