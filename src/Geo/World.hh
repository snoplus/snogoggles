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

    inline Volume& GetVolume() { return fVolume; }
    inline void SetVolume( Volume& volume ) { fVolume = volume; }

    inline std::map< std::string, VisAttributes* >& GetVisAttributeMap() 
    { return fVisAttributeMap; }
    void SetVisAttributeMap( std::map< std::string, VisAttributes* >& visAttributeMap );

    inline void Render();

private:

    void SetVisAttributes( Volume* volume );

    Volume fVolume;
    std::map< std::string, VisAttributes* > fVisAttributeMap;

}; // class World

void World::Render()
{
    fVolume.Render();
}

} // ::Viewer

#endif // __Viewer_World
