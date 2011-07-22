////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Geodesic3d
///
/// \brief   
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	12/07/11 : Olivia Wasalski - First Revision, New File \n
///
/// \details 	
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Geodesic3d__
#define __Viewer_Frames_Geodesic3d__

#include <Viewer/WorldBase3d.hh>
#include <Viewer/XMLLoader3d.hh>
#include <Viewer/WorldManager3d.hh>
#include <string>

namespace Viewer {
namespace Frames {

class Geodesic3d : public WorldBase3d {

public:

    Geodesic3d() : WorldBase3d( new XMLLoader3d( "geodesic.xml" ), new WorldManager3d ) { }

    static std::string Name() { return "Geodesic"; }
    std::string GetName() { return Name(); }

    void CreateGUIObjects( GUIManager& g, const sf::Rect<double>& optionsArea ) { }
    virtual void LoadConfiguration( ConfigurationTable* configTable ) { }
    virtual void SaveConfiguration( ConfigurationTable* configTable ) { }
    virtual void EventLoop( const GUIReturn& g ) { }
    void RenderGeometry() { fManager->RenderPolygonMode( GL_LINE ); }

}; // class Geodesic3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_Geodesic3d__
