////////////////////////////////////////////////////////////////////////
/// \class Viewer::Geodesic3d
///
/// \brief   The base class for all 3d modules
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original Geodesic3d class to take account
///          of codebase changes.
///          Geo manager module implementation that renders a geodesic
///          sphere. Utilizes the GeodesicSphere singleton to store the
///          VBOs necessary. A single GUI check box to enable or disable
///          rendering the geometry. Standard geometry. \n
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_Geodesic3d__
#define __Viewer_Geodesic3d__

#include <Viewer/Module3d.hh>

namespace Viewer
{

class Geodesic3d : public Module3d
{
public:
  Geodesic3d( RectPtr rect ) : Module3d( rect ), fDisplay( true ) { }
  virtual ~Geodesic3d() { }
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process data into renderable format, Nothing to do here
  virtual void ProcessData( const RenderState& renderState ) { };
  /// Render all 3d objects
  virtual void Render3d();
  /// Return the module name
  virtual std::string GetName() { return Geodesic3d::Name(); }
  static std::string Name() { return std::string( "Geodesic3d" ); }
protected:
  bool fDisplay; /// < Show the geo?
};

} //::Viewer

#endif
