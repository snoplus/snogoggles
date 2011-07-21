////////////////////////////////////////////////////////////////////////
/// \class Viewer::World
///
/// \brief   
///
/// \author  Olivia Wasalski <wasalski@triumf.ca>
///
/// REVISION HISTORY:\n
///     20/07/11 : Olivia Wasalski - First Revision, new file. \n
///
/// \detail  
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_World__
#define __Viewer_World__

#include <Viewer/Volume.hh>
#include <map>
#include <string>

namespace Viewer
{
    class VisAttributes;

class World
{
public:

    World( Volume& volume, std::map< std::string, VisAttributes* >& visAttributes );

    inline void Render();

    Volume fVolume;
    std::map< std::string, VisAttributes* > fVisAttributeMap;

private:

    void SetVisAttributes( Volume* volume );

}; // class World

void World::Render()
{
    fVolume.Render();
}

} // ::Viewer

#endif // __Viewer_World
