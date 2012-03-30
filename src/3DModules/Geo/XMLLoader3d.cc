#include <stdlib.h>
#include <sstream>
using namespace std;

#include <Viewer/XMLLoader3d.hh>
#include <Viewer/Configuration.hh>
#include <Viewer/ConfigurationTable.hh>
#include <Viewer/SerializableFactory.hh>
#include <Viewer/World.hh>

namespace Viewer {
namespace Frames {

World* XMLLoader3d::GetWorld()
{
  stringstream configFileName;
  configFileName << getenv( "VIEWERROOT" ) << "/data/" << fFilename;
  Configuration config = Configuration( configFileName.str(), false );

  std::vector< ConfigurationTable* >::iterator itr;
  itr = config.GetTableBegin();
  
  return SerializableFactory::GetInstance()->NewPtrFromThisTable< World >( *itr );
}


}; // namespace Frames
}; // namespace Viewer
