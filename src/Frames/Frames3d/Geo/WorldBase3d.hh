////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::WorldBase3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	21/07/11 : Olivia Wasalski - New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_WorldBase3d__
#define __Viewer_Frames_WorldBase3d__

#include <Viewer/GeoManager3d.hh>
#include <string>

namespace Viewer {
namespace Frames {

    class WorldLoader3d;
    class WorldManager3d;

class WorldBase3d : public GeoManager3d {

public:

    WorldBase3d( WorldLoader3d* loader, WorldManager3d* manager );
    virtual ~WorldBase3d();
    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
    virtual void LoadConfiguration( ConfigurationTable* configTable );
    virtual void SaveConfiguration( ConfigurationTable* configTable );
    virtual void LoadFile();
    virtual void EventLoop( const GUIReturn& g );
    virtual void RenderGeometry( );

protected:

    WorldLoader3d* fLoader;
    WorldManager3d* fManager;

}; // class WorldBase3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_WorldBase3d__
