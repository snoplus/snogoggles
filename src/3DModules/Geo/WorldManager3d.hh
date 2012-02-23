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
#include <Viewer/VisMap.hh>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

namespace Viewer {
    namespace GUIs {
        class CheckBoxLabel;
        class RadioCheckBoxes;
    };

    class World;
    class VisMap;
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
    inline VisMap* GetVisMap();

protected:

    World* fWorld;
    VisMap fVisMap;
    std::map< std::string, GUIs::CheckBoxLabel* > fGUIs;
    GUIs::RadioCheckBoxes* fRenderTypeGUI;

    enum GeoRenderType {
        SOLID,
        WIREFRAME,
        OUTLINE
    } fGeoRenderType;

}; // class WorldManager3d

VisMap* WorldManager3d::GetVisMap()
{
    return &fVisMap;
}

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_WorldManager3d__
