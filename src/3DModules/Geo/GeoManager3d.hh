////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::GeoManager3d
///
/// \brief   Abstract class which is responsible for loading
///	     and rendering geometry.
///
/// \author Olivia Wasalski <wasalski@triumf.ca>
///			    <oliviawasalski@triumf.ca>
///
/// REVISION HISTORY:\n
/// 	date : Olivia Wasalski - New File \n
///
/// \details 	The geometry manager is responsible for: \n
///
///		Loading geometry from a file. \n
///		Rendering the geometry. \n
///		Creating GUI objects which allow geometry options to be processed. \n
///		Appropriately responding when passed Viewer::Events. \n
///
////////////////////////////////////////////////////////////////////////


#ifndef __Viewer_Frames_GeoManager3d__
#define __Viewer_Frames_GeoManager3d__

#include <Viewer/Module3d.hh>
#include <string>

namespace Viewer {
namespace Frames {

class GeoManager3d : public Module3d {

public:

    virtual ~GeoManager3d() { }

    static std::string TableName() { return "GeoManager3d"; }
    std::string GetTableName() { return TableName(); }

    /// Loads a geometry file.
    virtual void LoadFile( ) = 0;
    static inline void LoadFileSafe( GeoManager3d* g )
    {
        if( g != NULL )
            g->LoadFile();
    }

}; // class GeoManager3d

}; // namespace Frames 
}; // namespace Viewer

#endif // __Viewer_Frames_GeoManager3d__
