////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::WorldManager3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	19/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_WorldManager3d__
#define __Viewer_Frames_WorldManager3d__

#include <Viewer/GeoManager3d.hh>
#include <SFML/OpenGL.hpp>
#include <string>
#include <map>

namespace Viewer {

    class World;

namespace Frames {

class WorldManager3d : public GeoManager3d {

public:

    WorldManager3d();
    ~WorldManager3d();
    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea ) { }
    void LoadFile( );
    virtual void LoadConfiguration( ConfigurationTable* configTable ) { }
    virtual void SaveConfiguration( ConfigurationTable* configTable ) { }
    virtual void EventLoop( const GUIReturn& g ) { }
    virtual void RenderGeometry( );

    virtual World* GetWorld() = 0;

protected:

    void RenderPolygonMode( GLenum e );
    World* fWorld;

    enum GeoRenderType {
        SOLID,
        WIREFRAME,
        OUTLINE
    } fGeoRenderType;

}; // class WorldManager3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_WorldManager3d__
