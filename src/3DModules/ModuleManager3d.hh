////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ModuleManager3d
///
/// \brief   Class which facilitates handling all of the possible modules. 
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	04/08/11 : Olivia Wasalski - New File \n
///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::ModuleManager3d::NoCameraError
///
/// \brief      Error that is thrown if a frame does not specify a camera manager.
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	13/07/11 : Olivia Wasalski - New File \n
///
/// \details    Without a camera manager, the OpenGL viewport is never set.
///             Therefore a regular 3D frame cannot operate without it.
///             Exception is thrown if the child frame who owns the module
///             manager does not specify a camera manager. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_ModuleManager3d__
#define __Viewer_Frames_ModuleManager3d__

#include <string>
#include <vector>
#include <SFML/Graphics/Rect.hpp>

#include <Viewer/RectPtr.hh>

namespace Viewer {

	class ConfigurationTable;
	class RWWrapper;
	class Rect;
    class RenderState;

namespace Frames {

    class Module3d;
    class CameraManager3d;
    class HitManager3d;
    class TrackManager3d;
    class GeoManager3d;
    class FitterManager3d;
    class Axes3d;
    enum ModuleTypes { CAMERA=0, HIT=1, TRACK=2, GEO=3, FITTER=4, AXES=5 };

class ModuleManager3d {
public:

    class NoCameraError {
    public:
        NoCameraError( ) { }
    };

	ModuleManager3d();
    ~ModuleManager3d();

  /// Set the Modules newed elsewhere
  void SetAllModules( CameraManager3d* camera, 
                      HitManager3d* hits, 
                      TrackManager3d* tracks,
                      GeoManager3d* geo,
                      FitterManager3d* fitter );
  /// Delete the modules
  void DeleteAllModules();
  /// Initiliase before an event is loaded
  void PreInitialise( const ConfigurationTable* configTable );
  /// Initialise the modules after an event is loaded
  void PostInitialise( const ConfigurationTable* configTable );
  /// Save the modules' configuration
  void SaveConfiguration( ConfigurationTable* configTable );
    void EventLoop();
    void ProcessData( const RenderState& renderState );
    void Render2d( RWWrapper& windowApp, const RenderState& renderState );
    void Render3d( RectPtr viewport, const RenderState& renderState );

    std::vector<Module3d*> fModules;


}; // class ModuleManager3d

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_ModuleManager3d__
