////////////////////////////////////////////////////////////////////////
/// \class Viewer::DefaultTracks3d
///
/// \brief   Renders tracks to the screen
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original DefaultTracks3d class to take account
///          of codebase changes.
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DefaultTracks3d__
#define __Viewer_DefaultTracks3d__

#include <map>
#include <string>

#include <Viewer/Module3d.hh>
#include <Viewer/TrackBuffer.hh>

namespace Viewer
{

class DefaultTracks3d : public Module3d
{
public:
  DefaultTracks3d( RectPtr rect ) : Module3d( rect ), fDisplayAll( true ), fDisplayFull( true ) { }
  virtual ~DefaultTracks3d() { }
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process data into renderable format, Nothing to do here
  virtual void ProcessData( const RenderState& renderState );
  /// Render all 3d objects
  virtual void Render3d();
  /// Return the module name
  virtual std::string GetName() { return DefaultTracks3d::Name(); }
  static std::string Name() { return std::string( "DefaultTracks3d" ); }
  
protected:
  TrackBuffer fTrackBuffer; /// < VBO for tracks
  std::map<std::string, bool> fDisplayParticle; /// < Display particle by name
  
  bool fDisplayAll; /// < Display all the tracks
  bool fDisplayFull; /// < Display the full track
};

} //::Viewer

#endif
