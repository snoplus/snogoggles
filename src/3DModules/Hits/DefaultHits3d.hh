////////////////////////////////////////////////////////////////////////
/// \class Viewer::DefaultHits3d
///
/// \brief   The base class for all 3d modules
///
/// \author  Olivia Wasalski <oliviawasalski@gmail.ca>
///          Phil Jones <p.g.jones@qmul.ac.uk>
///
/// REVISION HISTORY:\n
///     06/04/13 : P.Jones - New file, first revision \n
///
/// \detail  Modification of the original DefaultHits3d class to take account
///          of codebase changes.
///             Filters hits if either the render state or the current EV
///             changes. Stores each hit 2 ways, as a full hexagon and an
///             outline of a hexagon in 2 seperate VBOs. The full hexagon hits
///             are rendered with the depth buffer enabled, and the outline
///             hits are rendered with the depth buffer disabled to create
///             the effect that the hits in the back are outlines. Also has
///             a mode where it all of the PMT array. \n 
///
////////////////////////////////////////////////////////////////////////

#ifndef __Viewer_DefaultHits3d__
#define __Viewer_DefaultHits3d__

#include <Viewer/Module3d.hh>
#include <Viewer/HitBuffer.hh>

namespace Viewer
{

class DefaultHits3d : public Module3d
{
public:
  DefaultHits3d( RectPtr rect ) : Module3d( rect ), fDisplayAll( true ), fDisplayFront( true ) { }
  virtual ~DefaultHits3d() { }
  /// The event loop
  virtual void EventLoop();
  /// Save the current configuration
  virtual void SaveConfiguration( ConfigurationTable* configTable );
  /// Initialise without using the DataStore
  virtual void PreInitialise( const ConfigurationTable* configTable );
  /// Initilaise with DataStore access, Nothing to do here
  virtual void PostInitialise( const ConfigurationTable* configTable ) { };
  /// Process event data
  virtual void ProcessEvent( const RenderState& renderState );
  /// Process run data
  virtual void ProcessRun();
  /// Render all 3d objects
  virtual void Render3d();
  /// Return the module name
  virtual std::string GetName() { return DefaultHits3d::Name(); }
  static std::string Name() { return std::string( "DefaultHits3d" ); }
protected:
  HitBuffer fPMTListBuffer; /// < VBO for all PMTs
  HitBuffer fFullBuffer; /// < VBO for full PMTs 
  HitBuffer fOutlineBuffer; /// < VBO for wireframe PMTs

  bool fDisplayAll; /// Display all channels (even non hit ones)
  bool fDisplayFront; /// < Display only the front/nearest camera hits?
};

} //::Viewer

#endif
