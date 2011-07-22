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

#include <Viewer/GUIManager.hh>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

namespace Viewer {

    class World;
    class VisAttributes;
    class ConfigurationTable;

namespace Frames {

class WorldManager3d {

public:

    WorldManager3d();
    ~WorldManager3d();
    virtual void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea );
    void SetWorld( World* world );
    virtual void LoadConfiguration( ConfigurationTable* configTable );
    virtual void SaveConfiguration( ConfigurationTable* configTable );
    virtual void EventLoop( );
    virtual void RenderGeometry( );
    void RenderOutline();
    void RenderPolygonMode( GLenum e );

protected:

    virtual void LoadVisAttributes( ConfigurationTable* configTable );
    virtual void SaveVisAttributes( ConfigurationTable* configTable );

    World* fWorld;
    std::map< std::string, VisAttributes* > fMap;

    enum GeoRenderType {
        SOLID,
        WIREFRAME,
        OUTLINE
    } fGeoRenderType;

}; // class WorldManager3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_WorldManager3d__
