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

////////////////////////////////////////////////////////////////////////
/// \class Viewer::World::NoVisAttributesError
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
#include <Viewer/Serializable.hh>
#include <string>
#include <stdexcept>

namespace Viewer
{

class World : public Serializable
{
public:

    World() { }
    World( Volume& volume );

    inline const Volume& GetVolume() const;
    inline void SetVolume( Volume& volume );

    inline void SetVisibility( const std::string& name, bool visible );
    inline bool IsVisible( const std::string& name ) const;

    inline void Render();

    void Load( const ConfigurationTable* configTable );
    void Save( ConfigurationTable* configTable ) const;

private:

    void SetVisAttributes( Volume* volume );

    Volume fVolume;

}; // class World

////////////////////////////////////////////////////////////////////////
// inline methods
////////////////////////////////////////////////////////////////////////

const Volume& World::GetVolume() const
{
    return fVolume;
}

void World::SetVolume( Volume& volume )
{
    fVolume = volume;
}


void World::Render()
{
    fVolume.Render();
}

void World::SetVisibility( const std::string& name, bool visible )
{

}

bool World::IsVisible( const std::string& name ) const
{

}

} // ::Viewer

#endif // __Viewer_World
