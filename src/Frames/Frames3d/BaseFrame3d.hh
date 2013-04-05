////////////////////////////////////////////////////////////////////////
/// \class Viewer::Frames::BaseFrame3d
///
/// \brief   3D frame abstract class - uses module manager to implement 
///          mandatory frame methods. \n
///
/// \author Olivia Wasalski <wasalski@triumf.ca> 
///			    <oliviawasalski@gmail.com>
///
/// REVISION HISTORY:\n
/// 	04/08/11 : Olivia Wasalski - New File \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Frames_BaseFrame3d__
#define __Viewer_Frames_BaseFrame3d__

#include <SFML/Graphics/Rect.hpp>

#include <Viewer/Rect.hh>
#include <Viewer/Frame.hh>

namespace Viewer {

	class ConfigurationTable;
	class RWWrapper;

namespace Frames {

	class ModuleManager3d;

class BaseFrame3d : public Frame {
public:
  BaseFrame3d( RectPtr rect );
  virtual ~BaseFrame3d();
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access
  virtual void PostInitialise( const ConfigurationTable* configTable );
  /// Save the configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  virtual void EventLoop();
  virtual void ProcessData( const RenderState& renderState );
  virtual void Render2d( RWWrapper& renderApp, const RenderState& renderState );
  virtual void Render3d( RWWrapper& renderApp, const RenderState& renderState );
  
  virtual sf::Rect< double > GetViewportArea() = 0;  
protected:
  virtual ModuleManager3d* CreateModuleManager() = 0;
  /// Create the modules' GUI objects
  virtual void CreateGUIObjects() = 0;

  ModuleManager3d* fModuleManager;
}; // class BaseFrame3d

}; // namespace Frames
}; // namespace Viewer

#endif // __Viewer_Frames_BaseFrame3d__
