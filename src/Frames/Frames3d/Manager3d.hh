////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Manager3d
///
/// \brief   	This class manages independent, abstract modules to 
///		make up a complete 3d frame. 
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	05/07/11 : Olivia Wasalski - New File \n
///     06/07/11 : Olivia Wasalski - Now inherits from Frame class instead
///              of Frame3d class. Namespace change to reflect this. \n
///     06/07/11 : Olivia Wasalski - Split the load configuration method. \n
///     12/07/11 : Olivia Wasalski - Added x, y and z axes. \n
///     13/07/11 : Olivia Wasalski - Added function to delete all modules,
///                fixed a couple of other bugs. \n
///     15/07/11 : Olivia Wasalski - Uses lazy initialization. Initializes 
///              the first time the render3d function is called. \n
///
/// \details	The design for the 3D aspects of the viewer is modular 
///		in nature. The Manager3d class combines a series of 
///		independent modules represented by abstract classes. 
///		The goal of this design is to be flexible and easily 
///		extensible. This class is responsible for: \n 
///
///		Calling the appropriate initialization, rendering and 
///		event handling functions in the modules. \n
///		Rendering the backdrop and labels. \n
///		Managing the areas where modules can draw GUI objects. \n
///		Managing the area where the 3d display is drawn. \n 
///
///		There are 5 modules in total: CameraManager3d, HitManager3d, 
///		TrackManager3d, GeoManager3d and FitterManager3d. A 
///		standard 3D frame is built up of 1-5 of these modules. 
///		Each module is responsible for a separate task, as well as 
///		creating their own GUI objects, handling UI Events from 
///		their GUI objects and saving view aspects in an XML file. 
///		Each module has an area where the module's GUI objects can 
///		be drawn. This area is passed to each module in the frame 
///		coordinate system. 
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::Manager3d::NoCameraError
///
/// \brief   	
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	13/07/11 : Olivia Wasalski - New File \n
///
/// \details
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_Manager3d__
#define __Viewer_Frames_Manager3d__

#include <Viewer/Frame.hh>
#include <string>

namespace Viewer {

    class RWWrapper;
    class ConfigurationTable;

namespace Frames {

    class CameraManager3d;
    class HitManager3d;
    class TrackManager3d;
    class GeoManager3d;
    class FitterManager3d;

    class Axes3d;

class Manager3d : public Frame {

public:

    class NoCameraError
    {
    public:
        NoCameraError( ) { }
    };

    //Manager3d();

    Manager3d( const std::string& options );

    /// The destructor for the Manager3d class deletes the insances of the modules that it holds.
    ~Manager3d();

    void SetAllModules( 
        CameraManager3d* camera, 
        HitManager3d* hits, 
        TrackManager3d* tracks,
        GeoManager3d* geo,
        FitterManager3d* fitter
       );

    void DeleteAllModules();

    void Initialise() { }

    void CreateGUIObjects();

    void LoadConfiguration( ConfigurationTable& configTable );

    /// Saves all necessary configurations of the Manager3d class
    void SaveConfiguration( ConfigurationTable& configTable );

    /// Calls all of the event loops of all of the modules.
    void EventLoop();

    void Render2d( RWWrapper& windowApp );

    void Render3d();

private:

    void LateInitialise();

    void LoadModuleConfigurations( ConfigurationTable& configTable );

    void SaveModuleConfigurations( ConfigurationTable& configTable );

    CameraManager3d*    fCameraManager;     ///< The camera manager	
    HitManager3d*       fHitManager;        ///< The hit manager.
    TrackManager3d*     fTrackManager;      ///< The track manager.
    GeoManager3d*       fGeoManager;        ///< The geometry manager.
    FitterManager3d*    fFitterManager;	    ///< The fitter manager.

    bool fDisplayAxis;
    Axes3d* fAxes;
    static const std::string DISPLAY_AXIS_TAG;

    bool fInitialised;
    sf::Rect< double > fViewportArea;

}; // class Manager3d

}; // namespace Frames

}; // namespace Viewer

#endif // __Viewer_Frames_Manager3d__
