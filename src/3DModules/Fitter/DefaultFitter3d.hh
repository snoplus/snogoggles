////////////////////////////////////////////////////////////////////////
/// \class Viewer::DefaultFitter3d
///
/// \brief   Responsible for filtering and rendering reconstructed vertices.
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     07/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original DefaultFitter3d class to take account
///          of codebase changes.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DefaultFitter3d__
#define __Viewer_DefaultFitter3d__

#include <Viewer/Module3d.hh>
#include <Viewer/ReconBuffer.hh>

namespace Viewer
{

class DefaultFitter3d : public Module3d
{
public:
  DefaultFitter3d( RectPtr rect ) : Module3d( rect ) { }
  virtual ~DefaultFitter3d() { }
  /// The event loop
  virtual void EventLoop() { };
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable ) { };
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable ) { };
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process event data
  virtual void ProcessEvent( const RenderState& renderState );
  /// Process run data
  virtual void ProcessRun() { };
  /// Render all 3d objects
  virtual void Render3d();
  /// Return the module name
  virtual std::string GetName() { return DefaultFitter3d::Name(); }
  static std::string Name() { return std::string( "DefaultFitter3d" ); }

protected:
  ReconBuffer fBuffer;
};

} //::Viewer

#endif
