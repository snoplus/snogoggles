#include <Viewer/Module3dFactory.hh>
#include <Viewer/Axes3d.hh>
#include <Viewer/Arcball3d.hh>
#include <Viewer/DefaultHits3d.hh>
#include <Viewer/DefaultTracks3d.hh>
#include <Viewer/DefaultFitter3d.hh>
#include <Viewer/Geodesic3d.hh>
using namespace Viewer;

Module3dFactory::Module3dFactory()
{
  Register( Axes3d::Name(), new Module3dAlloc<Axes3d>() );
  Register( Arcball3d::Name(), new Module3dAlloc<Arcball3d>() );
  Register( DefaultHits3d::Name(), new Module3dAlloc<DefaultHits3d>() );
  Register( DefaultTracks3d::Name(), new Module3dAlloc<DefaultTracks3d>() );
  Register( DefaultFitter3d::Name(), new Module3dAlloc<DefaultFitter3d>() );
  Register( Geodesic3d::Name(), new Module3dAlloc<Geodesic3d>() );
}
